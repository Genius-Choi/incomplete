static void intra_prediction_unit(HEVCContext *s, int x0, int y0,
                                  int log2_cb_size)
{
    HEVCLocalContext *lc = s->HEVClc;
    static const uint8_t intra_chroma_table[4] = { 0, 26, 10, 1 };
    uint8_t prev_intra_luma_pred_flag[4];
    int split   = lc->cu.part_mode == PART_NxN;
    int pb_size = (1 << log2_cb_size) >> split;
    int side    = split + 1;
    int chroma_mode;
    int i, j;

    for (i = 0; i < side; i++)
        for (j = 0; j < side; j++)
            prev_intra_luma_pred_flag[2 * i + j] = ff_hevc_prev_intra_luma_pred_flag_decode(s);

    for (i = 0; i < side; i++) {
        for (j = 0; j < side; j++) {
            if (prev_intra_luma_pred_flag[2 * i + j])
                lc->pu.mpm_idx = ff_hevc_mpm_idx_decode(s);
            else
                lc->pu.rem_intra_luma_pred_mode = ff_hevc_rem_intra_luma_pred_mode_decode(s);

            lc->pu.intra_pred_mode[2 * i + j] =
                luma_intra_pred_mode(s, x0 + pb_size * j, y0 + pb_size * i, pb_size,
                                     prev_intra_luma_pred_flag[2 * i + j]);
        }
    }

    if (s->ps.sps->chroma_format_idc == 3) {
        for (i = 0; i < side; i++) {
            for (j = 0; j < side; j++) {
                lc->pu.chroma_mode_c[2 * i + j] = chroma_mode = ff_hevc_intra_chroma_pred_mode_decode(s);
                if (chroma_mode != 4) {
                    if (lc->pu.intra_pred_mode[2 * i + j] == intra_chroma_table[chroma_mode])
                        lc->pu.intra_pred_mode_c[2 * i + j] = 34;
                    else
                        lc->pu.intra_pred_mode_c[2 * i + j] = intra_chroma_table[chroma_mode];
                } else {
                    lc->pu.intra_pred_mode_c[2 * i + j] = lc->pu.intra_pred_mode[2 * i + j];
                }
            }
        }
    } else if (s->ps.sps->chroma_format_idc == 2) {
        int mode_idx;
        lc->pu.chroma_mode_c[0] = chroma_mode = ff_hevc_intra_chroma_pred_mode_decode(s);
        if (chroma_mode != 4) {
            if (lc->pu.intra_pred_mode[0] == intra_chroma_table[chroma_mode])
                mode_idx = 34;
            else
                mode_idx = intra_chroma_table[chroma_mode];
        } else {
            mode_idx = lc->pu.intra_pred_mode[0];
        }
        lc->pu.intra_pred_mode_c[0] = tab_mode_idx[mode_idx];
    } else if (s->ps.sps->chroma_format_idc != 0) {
        chroma_mode = ff_hevc_intra_chroma_pred_mode_decode(s);
        if (chroma_mode != 4) {
            if (lc->pu.intra_pred_mode[0] == intra_chroma_table[chroma_mode])
                lc->pu.intra_pred_mode_c[0] = 34;
            else
                lc->pu.intra_pred_mode_c[0] = intra_chroma_table[chroma_mode];
        } else {
            lc->pu.intra_pred_mode_c[0] = lc->pu.intra_pred_mode[0];
        }
    }
}
