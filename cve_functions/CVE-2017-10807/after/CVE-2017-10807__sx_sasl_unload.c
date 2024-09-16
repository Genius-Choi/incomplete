static void _sx_sasl_unload(sx_plugin_t p) {
    _sx_sasl_t ctx = (_sx_sasl_t) p->private;
    int i;
    assert(ctx);

    if (ctx->gsasl_ctx != NULL) gsasl_done (ctx->gsasl_ctx);
    if (ctx->appname != NULL) free(ctx->appname);
    for (i = 0; i < SX_CONN_EXTERNAL_ID_MAX_COUNT; i++)
        if(ctx->ext_id[i] != NULL)
            free(ctx->ext_id[i]);
        else
            break;

    free(ctx);
}
