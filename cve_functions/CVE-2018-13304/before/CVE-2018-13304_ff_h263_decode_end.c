av_cold int ff_h263_decode_end(AVCodecContext *avctx)
{
    MpegEncContext *s = avctx->priv_data;

    ff_mpv_common_end(s);
    return 0;
}
