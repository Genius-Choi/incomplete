static CURLcode nss_load_cert(struct ssl_connect_data *ssl,
                              const char *filename, PRBool cacert)
{
  CURLcode result = (cacert)
    ? CURLE_SSL_CACERT_BADFILE
    : CURLE_SSL_CERTPROBLEM;

  /* libnsspem.so leaks memory if the requested file does not exist.  For more
   * details, go to <https://bugzilla.redhat.com/734760>. */
  if(is_file(filename))
    result = nss_create_object(ssl, CKO_CERTIFICATE, filename, cacert);

  if(!result && !cacert) {
    /* we have successfully loaded a client certificate */
    CERTCertificate *cert;
    char *nickname = NULL;
    char *n = strrchr(filename, '/');
    if(n)
      n++;

    /* The following undocumented magic helps to avoid a SIGSEGV on call
     * of PK11_ReadRawAttribute() from SelectClientCert() when using an
     * immature version of libnsspem.so.  For more details, go to
     * <https://bugzilla.redhat.com/733685>. */
    nickname = aprintf("PEM Token #1:%s", n);
    if(nickname) {
      cert = PK11_FindCertFromNickname(nickname, NULL);
      if(cert)
        CERT_DestroyCertificate(cert);

      free(nickname);
    }
  }

  return result;
}
