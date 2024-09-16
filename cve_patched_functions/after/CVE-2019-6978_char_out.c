char_out(int c, GifCtx *ctx)
{
        ctx->accum[ ctx->a_count++ ] = c;
        if( ctx->a_count >= 254 )
                flush_char(ctx);
}
