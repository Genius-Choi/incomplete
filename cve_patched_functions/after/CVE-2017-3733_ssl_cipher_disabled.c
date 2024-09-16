int ssl_cipher_disabled(SSL *s, const SSL_CIPHER *c, int op)
{
    if (c->algorithm_mkey & s->s3->tmp.mask_k
        || c->algorithm_auth & s->s3->tmp.mask_a)
        return 1;
    if (s->s3->tmp.max_ver == 0)
        return 1;
    if (!SSL_IS_DTLS(s) && ((c->min_tls > s->s3->tmp.max_ver)
                            || (c->max_tls < s->s3->tmp.min_ver)))
        return 1;
    if (SSL_IS_DTLS(s) && (DTLS_VERSION_GT(c->min_dtls, s->s3->tmp.max_ver)
                           || DTLS_VERSION_LT(c->max_dtls, s->s3->tmp.min_ver)))
        return 1;

    return !ssl_security(s, op, c->strength_bits, 0, (void *)c);
}
