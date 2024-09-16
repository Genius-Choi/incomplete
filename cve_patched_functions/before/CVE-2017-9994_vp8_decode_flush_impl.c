static void vp8_decode_flush_impl(AVCodecContext *avctx, int free_mem)
{
    VP8Context *s = avctx->priv_data;
    int i;

    for (i = 0; i < FF_ARRAY_ELEMS(s->frames); i++)
        vp8_release_frame(s, &s->frames[i]);
    memset(s->framep, 0, sizeof(s->framep));

    if (free_mem)
        free_buffers(s);
}
