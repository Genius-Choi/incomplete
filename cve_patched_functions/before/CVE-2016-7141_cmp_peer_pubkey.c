static CURLcode cmp_peer_pubkey(struct ssl_connect_data *connssl,
                                const char *pinnedpubkey)
{
  CURLcode result = CURLE_SSL_PINNEDPUBKEYNOTMATCH;
  struct Curl_easy *data = connssl->data;
  CERTCertificate *cert;

  if(!pinnedpubkey)
    /* no pinned public key specified */
    return CURLE_OK;

  /* get peer certificate */
  cert = SSL_PeerCertificate(connssl->handle);
  if(cert) {
    /* extract public key from peer certificate */
    SECKEYPublicKey *pubkey = CERT_ExtractPublicKey(cert);
    if(pubkey) {
      /* encode the public key as DER */
      SECItem *cert_der = PK11_DEREncodePublicKey(pubkey);
      if(cert_der) {
        /* compare the public key with the pinned public key */
        result = Curl_pin_peer_pubkey(data, pinnedpubkey, cert_der->data,
                                      cert_der->len);
        SECITEM_FreeItem(cert_der, PR_TRUE);
      }
      SECKEY_DestroyPublicKey(pubkey);
    }
    CERT_DestroyCertificate(cert);
  }

  /* report the resulting status */
  switch(result) {
  case CURLE_OK:
    infof(data, "pinned public key verified successfully!\n");
    break;
  case CURLE_SSL_PINNEDPUBKEYNOTMATCH:
    failf(data, "failed to verify pinned public key");
    break;
  default:
    /* OOM, etc. */
    break;
  }

  return result;
}
