static int hevc_update_thread_context(AVCodecContext *dst,
                                      const AVCodecContext *src)
{
    HEVCContext *s  = dst->priv_data;
    HEVCContext *s0 = src->priv_data;
    int i, ret;

    if (!s->context_initialized) {
        ret = hevc_init_context(dst);
        if (ret < 0)
            return ret;
    }

    for (i = 0; i < FF_ARRAY_ELEMS(s->DPB); i++) {
        ff_hevc_unref_frame(s, &s->DPB[i], ~0);
        if (s0->DPB[i].frame->buf[0]) {
            ret = hevc_ref_frame(s, &s->DPB[i], &s0->DPB[i]);
            if (ret < 0)
                return ret;
        }
    }

    if (s->ps.sps != s0->ps.sps)
        s->ps.sps = NULL;
    for (i = 0; i < FF_ARRAY_ELEMS(s->ps.vps_list); i++) {
        av_buffer_unref(&s->ps.vps_list[i]);
        if (s0->ps.vps_list[i]) {
            s->ps.vps_list[i] = av_buffer_ref(s0->ps.vps_list[i]);
            if (!s->ps.vps_list[i])
                return AVERROR(ENOMEM);
        }
    }

    for (i = 0; i < FF_ARRAY_ELEMS(s->ps.sps_list); i++) {
        av_buffer_unref(&s->ps.sps_list[i]);
        if (s0->ps.sps_list[i]) {
            s->ps.sps_list[i] = av_buffer_ref(s0->ps.sps_list[i]);
            if (!s->ps.sps_list[i])
                return AVERROR(ENOMEM);
        }
    }

    for (i = 0; i < FF_ARRAY_ELEMS(s->ps.pps_list); i++) {
        av_buffer_unref(&s->ps.pps_list[i]);
        if (s0->ps.pps_list[i]) {
            s->ps.pps_list[i] = av_buffer_ref(s0->ps.pps_list[i]);
            if (!s->ps.pps_list[i])
                return AVERROR(ENOMEM);
        }
    }

    if (s->ps.sps != s0->ps.sps)
        if ((ret = set_sps(s, s0->ps.sps, src->pix_fmt)) < 0)
            return ret;

    s->seq_decode = s0->seq_decode;
    s->seq_output = s0->seq_output;
    s->pocTid0    = s0->pocTid0;
    s->max_ra     = s0->max_ra;
    s->eos        = s0->eos;
    s->no_rasl_output_flag = s0->no_rasl_output_flag;

    s->is_nalff        = s0->is_nalff;
    s->nal_length_size = s0->nal_length_size;

    s->threads_number      = s0->threads_number;
    s->threads_type        = s0->threads_type;

    if (s0->eos) {
        s->seq_decode = (s->seq_decode + 1) & 0xff;
        s->max_ra = INT_MAX;
    }

    s->sei.frame_packing        = s0->sei.frame_packing;
    s->sei.display_orientation  = s0->sei.display_orientation;
    s->sei.mastering_display    = s0->sei.mastering_display;
    s->sei.content_light        = s0->sei.content_light;
    s->sei.alternative_transfer = s0->sei.alternative_transfer;

    return 0;
}
