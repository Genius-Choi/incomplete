SSL_SESSION *(*SSL_CTX_sess_get_get_cb(SSL_CTX *ctx)) (SSL *ssl,
                                                       unsigned char *data,
                                                       int len, int *copy) {
    return ctx->get_session_cb;
}
