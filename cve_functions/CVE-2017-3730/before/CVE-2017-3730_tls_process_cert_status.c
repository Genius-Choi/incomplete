MSG_PROCESS_RETURN tls_process_cert_status(SSL *s, PACKET *pkt)
{
    int al;
    unsigned long resplen;
    unsigned int type;

    if (!PACKET_get_1(pkt, &type)
        || type != TLSEXT_STATUSTYPE_ocsp) {
        al = SSL_AD_DECODE_ERROR;
        SSLerr(SSL_F_TLS_PROCESS_CERT_STATUS, SSL_R_UNSUPPORTED_STATUS_TYPE);
        goto f_err;
    }
    if (!PACKET_get_net_3(pkt, &resplen)
        || PACKET_remaining(pkt) != resplen) {
        al = SSL_AD_DECODE_ERROR;
        SSLerr(SSL_F_TLS_PROCESS_CERT_STATUS, SSL_R_LENGTH_MISMATCH);
        goto f_err;
    }
    s->tlsext_ocsp_resp = OPENSSL_malloc(resplen);
    if (s->tlsext_ocsp_resp == NULL) {
        al = SSL_AD_INTERNAL_ERROR;
        SSLerr(SSL_F_TLS_PROCESS_CERT_STATUS, ERR_R_MALLOC_FAILURE);
        goto f_err;
    }
    if (!PACKET_copy_bytes(pkt, s->tlsext_ocsp_resp, resplen)) {
        al = SSL_AD_DECODE_ERROR;
        SSLerr(SSL_F_TLS_PROCESS_CERT_STATUS, SSL_R_LENGTH_MISMATCH);
        goto f_err;
    }
    s->tlsext_ocsp_resplen = resplen;
    return MSG_PROCESS_CONTINUE_READING;
 f_err:
    ssl3_send_alert(s, SSL3_AL_FATAL, al);
    ossl_statem_set_error(s);
    return MSG_PROCESS_ERROR;
}
