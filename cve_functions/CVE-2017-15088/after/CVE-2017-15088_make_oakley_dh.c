make_oakley_dh(uint8_t *prime, size_t len)
{
    DH *dh = NULL;
    BIGNUM *p = NULL, *q = NULL, *g = NULL;

    p = BN_bin2bn(prime, len, NULL);
    if (p == NULL)
        goto cleanup;
    q = BN_new();
    if (q == NULL)
        goto cleanup;
    if (!BN_rshift1(q, p))
        goto cleanup;
    g = BN_new();
    if (g == NULL)
        goto cleanup;
    if (!BN_set_word(g, DH_GENERATOR_2))
        goto cleanup;

    dh = DH_new();
    if (dh == NULL)
        goto cleanup;
    DH_set0_pqg(dh, p, q, g);
    p = g = q = NULL;

cleanup:
    BN_free(p);
    BN_free(q);
    BN_free(g);
    return dh;
}
