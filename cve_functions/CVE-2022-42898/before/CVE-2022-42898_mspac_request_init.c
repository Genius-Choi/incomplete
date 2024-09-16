mspac_request_init(krb5_context kcontext,
                   krb5_authdata_context context,
                   void *plugin_context,
                   void **request_context)
{
    struct mspac_context *pacctx;

    pacctx = (struct mspac_context *)malloc(sizeof(*pacctx));
    if (pacctx == NULL)
        return ENOMEM;

    pacctx->pac = NULL;

    *request_context = pacctx;

    return 0;
}
