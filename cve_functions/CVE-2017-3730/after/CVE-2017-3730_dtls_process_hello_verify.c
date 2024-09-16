MSG_PROCESS_RETURN dtls_process_hello_verify(SSL *s, PACKET *pkt)
{
    int al;
    unsigned int cookie_len;
    PACKET cookiepkt;

    if (!PACKET_forward(pkt, 2)
        || !PACKET_get_length_prefixed_1(pkt, &cookiepkt)) {
        al = SSL_AD_DECODE_ERROR;
        SSLerr(SSL_F_DTLS_PROCESS_HELLO_VERIFY, SSL_R_LENGTH_MISMATCH);
        goto f_err;
    }

    cookie_len = PACKET_remaining(&cookiepkt);
    if (cookie_len > sizeof(s->d1->cookie)) {
        al = SSL_AD_ILLEGAL_PARAMETER;
        SSLerr(SSL_F_DTLS_PROCESS_HELLO_VERIFY, SSL_R_LENGTH_TOO_LONG);
        goto f_err;
    }

    if (!PACKET_copy_bytes(&cookiepkt, s->d1->cookie, cookie_len)) {
        al = SSL_AD_DECODE_ERROR;
        SSLerr(SSL_F_DTLS_PROCESS_HELLO_VERIFY, SSL_R_LENGTH_MISMATCH);
        goto f_err;
    }
    s->d1->cookie_len = cookie_len;

    return MSG_PROCESS_FINISHED_READING;
 f_err:
    ssl3_send_alert(s, SSL3_AL_FATAL, al);
    ossl_statem_set_error(s);
    return MSG_PROCESS_ERROR;
}
