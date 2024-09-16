pkinit_fini_identity_crypto(pkinit_identity_crypto_context idctx)
{
    if (idctx == NULL)
        return;

    pkiDebug("%s: freeing ctx at %p\n", __FUNCTION__, idctx);
    if (idctx->deferred_ids != NULL)
        pkinit_free_deferred_ids(idctx->deferred_ids);
    free(idctx->identity);
    pkinit_fini_certs(idctx);
    pkinit_fini_pkcs11(idctx);
    free(idctx);
}
