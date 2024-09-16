static CURLcode nss_setup_connect(struct connectdata *conn, int sockindex)
{
  PRFileDesc *model = NULL;
  PRFileDesc *nspr_io = NULL;
  PRFileDesc *nspr_io_stub = NULL;
  PRBool ssl_no_cache;
  PRBool ssl_cbc_random_iv;
  struct Curl_easy *data = conn->data;
  curl_socket_t sockfd = conn->sock[sockindex];
  struct ssl_connect_data *connssl = &conn->ssl[sockindex];
  CURLcode result;

  SSLVersionRange sslver = {
    SSL_LIBRARY_VERSION_TLS_1_0,  /* min */
    SSL_LIBRARY_VERSION_TLS_1_0   /* max */
  };

  connssl->data = data;

  /* list of all NSS objects we need to destroy in Curl_nss_close() */
  connssl->obj_list = Curl_llist_alloc(nss_destroy_object);
  if(!connssl->obj_list)
    return CURLE_OUT_OF_MEMORY;

  /* FIXME. NSS doesn't support multiple databases open at the same time. */
  PR_Lock(nss_initlock);
  result = nss_init(conn->data);
  if(result) {
    PR_Unlock(nss_initlock);
    goto error;
  }

  result = CURLE_SSL_CONNECT_ERROR;

  if(!mod) {
    char *configstring = aprintf("library=%s name=PEM", pem_library);
    if(!configstring) {
      PR_Unlock(nss_initlock);
      goto error;
    }
    mod = SECMOD_LoadUserModule(configstring, NULL, PR_FALSE);
    free(configstring);

    if(!mod || !mod->loaded) {
      if(mod) {
        SECMOD_DestroyModule(mod);
        mod = NULL;
      }
      infof(data, "WARNING: failed to load NSS PEM library %s. Using "
                  "OpenSSL PEM certificates will not work.\n", pem_library);
    }
  }

  PK11_SetPasswordFunc(nss_get_password);
  PR_Unlock(nss_initlock);

  model = PR_NewTCPSocket();
  if(!model)
    goto error;
  model = SSL_ImportFD(NULL, model);

  if(SSL_OptionSet(model, SSL_SECURITY, PR_TRUE) != SECSuccess)
    goto error;
  if(SSL_OptionSet(model, SSL_HANDSHAKE_AS_SERVER, PR_FALSE) != SECSuccess)
    goto error;
  if(SSL_OptionSet(model, SSL_HANDSHAKE_AS_CLIENT, PR_TRUE) != SECSuccess)
    goto error;

  /* do not use SSL cache if disabled or we are not going to verify peer */
  ssl_no_cache = (conn->ssl_config.sessionid && data->set.ssl.verifypeer) ?
    PR_FALSE : PR_TRUE;
  if(SSL_OptionSet(model, SSL_NO_CACHE, ssl_no_cache) != SECSuccess)
    goto error;

  /* enable/disable the requested SSL version(s) */
  if(nss_init_sslver(&sslver, data) != CURLE_OK)
    goto error;
  if(SSL_VersionRangeSet(model, &sslver) != SECSuccess)
    goto error;

  ssl_cbc_random_iv = !data->set.ssl_enable_beast;
#ifdef SSL_CBC_RANDOM_IV
  /* unless the user explicitly asks to allow the protocol vulnerability, we
     use the work-around */
  if(SSL_OptionSet(model, SSL_CBC_RANDOM_IV, ssl_cbc_random_iv) != SECSuccess)
    infof(data, "warning: failed to set SSL_CBC_RANDOM_IV = %d\n",
          ssl_cbc_random_iv);
#else
  if(ssl_cbc_random_iv)
    infof(data, "warning: support for SSL_CBC_RANDOM_IV not compiled in\n");
#endif

  if(data->set.ssl.cipher_list) {
    if(set_ciphers(data, model, data->set.ssl.cipher_list) != SECSuccess) {
      result = CURLE_SSL_CIPHER;
      goto error;
    }
  }

  if(!data->set.ssl.verifypeer && data->set.ssl.verifyhost)
    infof(data, "warning: ignoring value of ssl.verifyhost\n");

  /* bypass the default SSL_AuthCertificate() hook in case we do not want to
   * verify peer */
  if(SSL_AuthCertificateHook(model, nss_auth_cert_hook, conn) != SECSuccess)
    goto error;

  data->set.ssl.certverifyresult=0; /* not checked yet */
  if(SSL_BadCertHook(model, BadCertHandler, conn) != SECSuccess)
    goto error;

  if(SSL_HandshakeCallback(model, HandshakeCallback, conn) != SECSuccess)
    goto error;

  if(data->set.ssl.verifypeer) {
    const CURLcode rv = nss_load_ca_certificates(conn, sockindex);
    if(rv) {
      result = rv;
      goto error;
    }
  }

  if(data->set.ssl.CRLfile) {
    const CURLcode rv = nss_load_crl(data->set.ssl.CRLfile);
    if(rv) {
      result = rv;
      goto error;
    }
    infof(data, "  CRLfile: %s\n", data->set.ssl.CRLfile);
  }

  if(data->set.str[STRING_CERT]) {
    char *nickname = dup_nickname(data, STRING_CERT);
    if(nickname) {
      /* we are not going to use libnsspem.so to read the client cert */
      connssl->obj_clicert = NULL;
    }
    else {
      CURLcode rv = cert_stuff(conn, sockindex, data->set.str[STRING_CERT],
                               data->set.str[STRING_KEY]);
      if(rv) {
        /* failf() is already done in cert_stuff() */
        result = rv;
        goto error;
      }
    }

    /* store the nickname for SelectClientCert() called during handshake */
    connssl->client_nickname = nickname;
  }
  else
    connssl->client_nickname = NULL;

  if(SSL_GetClientAuthDataHook(model, SelectClientCert,
                               (void *)connssl) != SECSuccess) {
    result = CURLE_SSL_CERTPROBLEM;
    goto error;
  }

  /* wrap OS file descriptor by NSPR's file descriptor abstraction */
  nspr_io = PR_ImportTCPSocket(sockfd);
  if(!nspr_io)
    goto error;

  /* create our own NSPR I/O layer */
  nspr_io_stub = PR_CreateIOLayerStub(nspr_io_identity, &nspr_io_methods);
  if(!nspr_io_stub) {
    PR_Close(nspr_io);
    goto error;
  }

  /* make the per-connection data accessible from NSPR I/O callbacks */
  nspr_io_stub->secret = (void *)connssl;

  /* push our new layer to the NSPR I/O stack */
  if(PR_PushIOLayer(nspr_io, PR_TOP_IO_LAYER, nspr_io_stub) != PR_SUCCESS) {
    PR_Close(nspr_io);
    PR_Close(nspr_io_stub);
    goto error;
  }

  /* import our model socket onto the current I/O stack */
  connssl->handle = SSL_ImportFD(model, nspr_io);
  if(!connssl->handle) {
    PR_Close(nspr_io);
    goto error;
  }

  PR_Close(model); /* We don't need this any more */
  model = NULL;

  /* This is the password associated with the cert that we're using */
  if(data->set.str[STRING_KEY_PASSWD]) {
    SSL_SetPKCS11PinArg(connssl->handle, data->set.str[STRING_KEY_PASSWD]);
  }

#ifdef SSL_ENABLE_OCSP_STAPLING
  if(data->set.ssl.verifystatus) {
    if(SSL_OptionSet(connssl->handle, SSL_ENABLE_OCSP_STAPLING, PR_TRUE)
        != SECSuccess)
      goto error;
  }
#endif

#ifdef SSL_ENABLE_NPN
  if(SSL_OptionSet(connssl->handle, SSL_ENABLE_NPN, conn->bits.tls_enable_npn
                   ? PR_TRUE : PR_FALSE) != SECSuccess)
    goto error;
#endif

#ifdef SSL_ENABLE_ALPN
  if(SSL_OptionSet(connssl->handle, SSL_ENABLE_ALPN, conn->bits.tls_enable_alpn
                   ? PR_TRUE : PR_FALSE) != SECSuccess)
    goto error;
#endif

#if NSSVERNUM >= 0x030f04 /* 3.15.4 */
  if(data->set.ssl.falsestart) {
    if(SSL_OptionSet(connssl->handle, SSL_ENABLE_FALSE_START, PR_TRUE)
        != SECSuccess)
      goto error;

    if(SSL_SetCanFalseStartCallback(connssl->handle, CanFalseStartCallback,
        conn) != SECSuccess)
      goto error;
  }
#endif

#if defined(SSL_ENABLE_NPN) || defined(SSL_ENABLE_ALPN)
  if(conn->bits.tls_enable_npn || conn->bits.tls_enable_alpn) {
    int cur = 0;
    unsigned char protocols[128];

#ifdef USE_NGHTTP2
    if(data->set.httpversion >= CURL_HTTP_VERSION_2) {
      protocols[cur++] = NGHTTP2_PROTO_VERSION_ID_LEN;
      memcpy(&protocols[cur], NGHTTP2_PROTO_VERSION_ID,
          NGHTTP2_PROTO_VERSION_ID_LEN);
      cur += NGHTTP2_PROTO_VERSION_ID_LEN;
    }
#endif
    protocols[cur++] = ALPN_HTTP_1_1_LENGTH;
    memcpy(&protocols[cur], ALPN_HTTP_1_1, ALPN_HTTP_1_1_LENGTH);
    cur += ALPN_HTTP_1_1_LENGTH;

    if(SSL_SetNextProtoNego(connssl->handle, protocols, cur) != SECSuccess)
      goto error;
  }
#endif


  /* Force handshake on next I/O */
  if(SSL_ResetHandshake(connssl->handle, /* asServer */ PR_FALSE)
      != SECSuccess)
    goto error;

  /* propagate hostname to the TLS layer */
  if(SSL_SetURL(connssl->handle, conn->host.name) != SECSuccess)
    goto error;

  /* prevent NSS from re-using the session for a different hostname */
  if(SSL_SetSockPeerID(connssl->handle, conn->host.name) != SECSuccess)
    goto error;

  return CURLE_OK;

error:
  if(model)
    PR_Close(model);

  return nss_fail_connect(connssl, data, result);
}
