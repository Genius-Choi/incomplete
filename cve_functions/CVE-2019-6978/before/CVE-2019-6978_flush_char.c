flush_char(GifCtx *ctx)
{
        if( ctx->a_count > 0 ) {
                gdPutC( ctx->a_count, ctx->g_outfile );
                gdPutBuf( ctx->accum, ctx->a_count, ctx->g_outfile );
                ctx->a_count = 0;
        }
}
