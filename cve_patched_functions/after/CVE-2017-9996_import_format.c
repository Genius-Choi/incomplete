static void import_format(CDXLVideoContext *c, int linesize, uint8_t *out)
{
    memset(out, 0, linesize * c->avctx->height);

    switch (c->format) {
    case BIT_PLANAR:
        bitplanar2chunky(c, linesize, out);
        break;
    case BIT_LINE:
        bitline2chunky(c, linesize, out);
        break;
    case CHUNKY:
        chunky2chunky(c, linesize, out);
        break;
    }
}
