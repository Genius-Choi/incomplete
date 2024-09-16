int tls_construct_client_certificate(SSL *s)
{
    if (!ssl3_output_cert_chain(s,
                                (s->s3->tmp.cert_req ==
                                 2) ? NULL : s->cert->key)) {
        SSLerr(SSL_F_TLS_CONSTRUCT_CLIENT_CERTIFICATE, ERR_R_INTERNAL_ERROR);
        ssl3_send_alert(s, SSL3_AL_FATAL, SSL_AD_INTERNAL_ERROR);
        ossl_statem_set_error(s);
        return 0;
    }

    return 1;
}
