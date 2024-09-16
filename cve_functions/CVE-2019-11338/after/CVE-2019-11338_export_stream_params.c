static void export_stream_params(AVCodecContext *avctx, const HEVCParamSets *ps,
                                 const HEVCSPS *sps)
{
    const HEVCVPS *vps = (const HEVCVPS*)ps->vps_list[sps->vps_id]->data;
    const HEVCWindow *ow = &sps->output_window;
    unsigned int num = 0, den = 0;

    avctx->pix_fmt             = sps->pix_fmt;
    avctx->coded_width         = sps->width;
    avctx->coded_height        = sps->height;
    avctx->width               = sps->width  - ow->left_offset - ow->right_offset;
    avctx->height              = sps->height - ow->top_offset  - ow->bottom_offset;
    avctx->has_b_frames        = sps->temporal_layer[sps->max_sub_layers - 1].num_reorder_pics;
    avctx->profile             = sps->ptl.general_ptl.profile_idc;
    avctx->level               = sps->ptl.general_ptl.level_idc;

    ff_set_sar(avctx, sps->vui.sar);

    if (sps->vui.video_signal_type_present_flag)
        avctx->color_range = sps->vui.video_full_range_flag ? AVCOL_RANGE_JPEG
                                                            : AVCOL_RANGE_MPEG;
    else
        avctx->color_range = AVCOL_RANGE_MPEG;

    if (sps->vui.colour_description_present_flag) {
        avctx->color_primaries = sps->vui.colour_primaries;
        avctx->color_trc       = sps->vui.transfer_characteristic;
        avctx->colorspace      = sps->vui.matrix_coeffs;
    } else {
        avctx->color_primaries = AVCOL_PRI_UNSPECIFIED;
        avctx->color_trc       = AVCOL_TRC_UNSPECIFIED;
        avctx->colorspace      = AVCOL_SPC_UNSPECIFIED;
    }

    if (vps->vps_timing_info_present_flag) {
        num = vps->vps_num_units_in_tick;
        den = vps->vps_time_scale;
    } else if (sps->vui.vui_timing_info_present_flag) {
        num = sps->vui.vui_num_units_in_tick;
        den = sps->vui.vui_time_scale;
    }

    if (num != 0 && den != 0)
        av_reduce(&avctx->framerate.den, &avctx->framerate.num,
                  num, den, 1 << 30);
}
