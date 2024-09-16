int ff_vp8_decode_frame(AVCodecContext *avctx, void *data, int *got_frame,
                        AVPacket *avpkt)
{
    return vp78_decode_frame(avctx, data, got_frame, avpkt, IS_VP8);
}
