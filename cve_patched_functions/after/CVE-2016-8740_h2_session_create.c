h2_session *h2_session_create(conn_rec *c, h2_ctx *ctx, h2_workers *workers)
{
    return h2_session_create_int(c, NULL, ctx, workers);
}
