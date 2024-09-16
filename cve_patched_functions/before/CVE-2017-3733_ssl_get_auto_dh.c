DH *ssl_get_auto_dh(SSL *s)
{
    int dh_secbits = 80;
    if (s->cert->dh_tmp_auto == 2)
        return DH_get_1024_160();
    if (s->s3->tmp.new_cipher->algorithm_auth & (SSL_aNULL | SSL_aPSK)) {
        if (s->s3->tmp.new_cipher->strength_bits == 256)
            dh_secbits = 128;
        else
            dh_secbits = 80;
    } else {
        CERT_PKEY *cpk = ssl_get_server_send_pkey(s);
        dh_secbits = EVP_PKEY_security_bits(cpk->privatekey);
    }

    if (dh_secbits >= 128) {
        DH *dhp = DH_new();
        BIGNUM *p, *g;
        if (dhp == NULL)
            return NULL;
        g = BN_new();
        if (g != NULL)
            BN_set_word(g, 2);
        if (dh_secbits >= 192)
            p = BN_get_rfc3526_prime_8192(NULL);
        else
            p = BN_get_rfc3526_prime_3072(NULL);
        if (p == NULL || g == NULL || !DH_set0_pqg(dhp, p, NULL, g)) {
            DH_free(dhp);
            BN_free(p);
            BN_free(g);
            return NULL;
        }
        return dhp;
    }
    if (dh_secbits >= 112)
        return DH_get_2048_224();
    return DH_get_1024_160();
}
