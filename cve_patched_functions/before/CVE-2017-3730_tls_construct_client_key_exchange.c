int tls_construct_client_key_exchange(SSL *s)
{
    unsigned char *p;
    int len;
    size_t pskhdrlen = 0;
    unsigned long alg_k;
    int al = -1;

    alg_k = s->s3->tmp.new_cipher->algorithm_mkey;

    p = ssl_handshake_start(s);

    if ((alg_k & SSL_PSK)
        && !tls_construct_cke_psk_preamble(s, &p, &pskhdrlen, &al))
        goto err;

    if (alg_k & SSL_kPSK) {
        len = 0;
    } else if (alg_k & (SSL_kRSA | SSL_kRSAPSK)) {
        if (!tls_construct_cke_rsa(s, &p, &len, &al))
            goto err;
    } else if (alg_k & (SSL_kDHE | SSL_kDHEPSK)) {
        if (!tls_construct_cke_dhe(s, &p, &len, &al))
            goto err;
    } else if (alg_k & (SSL_kECDHE | SSL_kECDHEPSK)) {
        if (!tls_construct_cke_ecdhe(s, &p, &len, &al))
            goto err;
    } else if (alg_k & SSL_kGOST) {
        if (!tls_construct_cke_gost(s, &p, &len, &al))
            goto err;
    } else if (alg_k & SSL_kSRP) {
        if (!tls_construct_cke_srp(s, &p, &len, &al))
            goto err;
    } else {
        ssl3_send_alert(s, SSL3_AL_FATAL, SSL_AD_HANDSHAKE_FAILURE);
        SSLerr(SSL_F_TLS_CONSTRUCT_CLIENT_KEY_EXCHANGE, ERR_R_INTERNAL_ERROR);
        goto err;
    }

    len += pskhdrlen;

    if (!ssl_set_handshake_header(s, SSL3_MT_CLIENT_KEY_EXCHANGE, len)) {
        ssl3_send_alert(s, SSL3_AL_FATAL, SSL_AD_HANDSHAKE_FAILURE);
        SSLerr(SSL_F_TLS_CONSTRUCT_CLIENT_KEY_EXCHANGE, ERR_R_INTERNAL_ERROR);
        goto err;
    }

    return 1;
 err:
    if (al != -1)
        ssl3_send_alert(s, SSL3_AL_FATAL, al);
    OPENSSL_clear_free(s->s3->tmp.pms, s->s3->tmp.pmslen);
    s->s3->tmp.pms = NULL;
#ifndef OPENSSL_NO_PSK
    OPENSSL_clear_free(s->s3->tmp.psk, s->s3->tmp.psklen);
    s->s3->tmp.psk = NULL;
#endif
    ossl_statem_set_error(s);
    return 0;
}
