static int hls_pcm_sample(HEVCContext *s, int x0, int y0, int log2_cb_size)
{
    HEVCLocalContext *lc = s->HEVClc;
    GetBitContext gb;
    int cb_size   = 1 << log2_cb_size;
    ptrdiff_t stride0 = s->frame->linesize[0];
    ptrdiff_t stride1 = s->frame->linesize[1];
    ptrdiff_t stride2 = s->frame->linesize[2];
    uint8_t *dst0 = &s->frame->data[0][y0 * stride0 + (x0 << s->ps.sps->pixel_shift)];
    uint8_t *dst1 = &s->frame->data[1][(y0 >> s->ps.sps->vshift[1]) * stride1 + ((x0 >> s->ps.sps->hshift[1]) << s->ps.sps->pixel_shift)];
    uint8_t *dst2 = &s->frame->data[2][(y0 >> s->ps.sps->vshift[2]) * stride2 + ((x0 >> s->ps.sps->hshift[2]) << s->ps.sps->pixel_shift)];

    int length         = cb_size * cb_size * s->ps.sps->pcm.bit_depth +
                         (((cb_size >> s->ps.sps->hshift[1]) * (cb_size >> s->ps.sps->vshift[1])) +
                          ((cb_size >> s->ps.sps->hshift[2]) * (cb_size >> s->ps.sps->vshift[2]))) *
                          s->ps.sps->pcm.bit_depth_chroma;
    const uint8_t *pcm = skip_bytes(&lc->cc, (length + 7) >> 3);
    int ret;

    if (!s->sh.disable_deblocking_filter_flag)
        ff_hevc_deblocking_boundary_strengths(s, x0, y0, log2_cb_size);

    ret = init_get_bits(&gb, pcm, length);
    if (ret < 0)
        return ret;

    s->hevcdsp.put_pcm(dst0, stride0, cb_size, cb_size,     &gb, s->ps.sps->pcm.bit_depth);
    if (s->ps.sps->chroma_format_idc) {
        s->hevcdsp.put_pcm(dst1, stride1,
                           cb_size >> s->ps.sps->hshift[1],
                           cb_size >> s->ps.sps->vshift[1],
                           &gb, s->ps.sps->pcm.bit_depth_chroma);
        s->hevcdsp.put_pcm(dst2, stride2,
                           cb_size >> s->ps.sps->hshift[2],
                           cb_size >> s->ps.sps->vshift[2],
                           &gb, s->ps.sps->pcm.bit_depth_chroma);
    }

    return 0;
}
