static av_always_inline void set_ct_depth(HEVCContext *s, int x0, int y0,
                                          int log2_cb_size, int ct_depth)
{
    int length = (1 << log2_cb_size) >> s->ps.sps->log2_min_cb_size;
    int x_cb   = x0 >> s->ps.sps->log2_min_cb_size;
    int y_cb   = y0 >> s->ps.sps->log2_min_cb_size;
    int y;

    for (y = 0; y < length; y++)
        memset(&s->tab_ct_depth[(y_cb + y) * s->ps.sps->min_cb_width + x_cb],
               ct_depth, length);
}
