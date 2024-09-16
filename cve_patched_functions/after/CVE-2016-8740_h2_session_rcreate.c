h2_session *h2_session_rcreate(request_rec *r, h2_ctx *ctx, h2_workers *workers)
{
    return h2_session_create_int(r->connection, r, ctx, workers);
}
