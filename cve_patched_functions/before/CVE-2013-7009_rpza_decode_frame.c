static int rpza_decode_frame(AVCodecContext *avctx,
                             void *data, int *got_frame,
                             AVPacket *avpkt)
{
    const uint8_t *buf = avpkt->data;
    int buf_size = avpkt->size;
    RpzaContext *s = avctx->priv_data;
    int ret;

    s->buf = buf;
    s->size = buf_size;

    if ((ret = ff_reget_buffer(avctx, &s->frame)) < 0)
        return ret;

    rpza_decode_stream(s);

    if ((ret = av_frame_ref(data, &s->frame)) < 0)
        return ret;

    *got_frame      = 1;

    /* always report that the buffer was completely consumed */
    return buf_size;
}
