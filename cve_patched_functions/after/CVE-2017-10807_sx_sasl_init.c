int sx_sasl_init(sx_env_t env, sx_plugin_t p, va_list args) {
    const char *appname;
    sx_sasl_callback_t cb;
    void *cbarg;
    _sx_sasl_t ctx;
    int ret, i;

    _sx_debug(ZONE, "initialising sasl plugin");

    appname = va_arg(args, const char *);
    if(appname == NULL) {
        _sx_debug(ZONE, "appname was NULL, failing");
        return 1;
    }

    cb = va_arg(args, sx_sasl_callback_t);
    cbarg = va_arg(args, void *);

    ctx = (_sx_sasl_t) calloc(1, sizeof(struct _sx_sasl_st));

    ctx->appname = strdup(appname);
    ctx->cb = cb;
    ctx->cbarg = cbarg;
    for (i = 0; i < SX_CONN_EXTERNAL_ID_MAX_COUNT; i++)
        ctx->ext_id[i] = NULL;

    ret = gsasl_init(&ctx->gsasl_ctx);
    if(ret != GSASL_OK) {
        _sx_debug(ZONE, "couldn't initialize libgsasl (%d): %s", ret, gsasl_strerror (ret));
        free(ctx);
        return 1;
    }

    gsasl_callback_set (ctx->gsasl_ctx, &_sx_sasl_gsasl_callback);

    _sx_debug(ZONE, "sasl context initialised");

    p->private = (void *) ctx;

    p->unload = _sx_sasl_unload;
    p->wio = _sx_sasl_wio;
    p->rio = _sx_sasl_rio;

    p->stream = _sx_sasl_stream;
    p->features = _sx_sasl_features;
    p->process = _sx_sasl_process;

    p->free = _sx_sasl_free;

    return 0;
}
