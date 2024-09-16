static int find_cleanup_stream(h2_stream *stream, void *ictx)
{
    stream_sel_ctx *ctx = ictx;
    if (H2_STREAM_CLIENT_INITIATED(stream->id)) {
        if (!ctx->session->local.accepting
            && stream->id > ctx->session->local.accepted_max) {
            ctx->candidate = stream;
            return 0;
        }
    }
    else {
        if (!ctx->session->remote.accepting
            && stream->id > ctx->session->remote.accepted_max) {
            ctx->candidate = stream;
            return 0;
        }
    }
    return 1;
}
