pkinit_init_dh_params(pkinit_plg_crypto_context plgctx)
{
    krb5_error_code retval = ENOMEM;

    plgctx->dh_1024 = make_oakley_dh(oakley_1024, sizeof(oakley_1024));
    if (plgctx->dh_1024 == NULL)
        goto cleanup;

    plgctx->dh_2048 = make_oakley_dh(oakley_2048, sizeof(oakley_2048));
    if (plgctx->dh_2048 == NULL)
        goto cleanup;

    plgctx->dh_4096 = make_oakley_dh(oakley_4096, sizeof(oakley_4096));
    if (plgctx->dh_4096 == NULL)
        goto cleanup;

    retval = 0;

cleanup:
    if (retval)
        pkinit_fini_dh_params(plgctx);

    return retval;
}
