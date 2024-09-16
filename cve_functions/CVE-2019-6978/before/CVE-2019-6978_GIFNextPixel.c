GIFNextPixel(gdImagePtr im, GifCtx *ctx)
{
        int r;

        if( ctx->CountDown == 0 )
                return EOF;

        --(ctx->CountDown);

        r = gdImageGetPixel(im, ctx->curx, ctx->cury);

        BumpPixel(ctx);

        return r;
}
