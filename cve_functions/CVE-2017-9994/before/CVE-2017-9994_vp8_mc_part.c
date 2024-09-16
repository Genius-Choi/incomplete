void vp8_mc_part(VP8Context *s, VP8ThreadData *td, uint8_t *dst[3],
                 ThreadFrame *ref_frame, int x_off, int y_off,
                 int bx_off, int by_off, int block_w, int block_h,
                 int width, int height, VP56mv *mv)
{
    VP56mv uvmv = *mv;

    /* Y */
    vp8_mc_luma(s, td, dst[0] + by_off * s->linesize + bx_off,
                ref_frame, mv, x_off + bx_off, y_off + by_off,
                block_w, block_h, width, height, s->linesize,
                s->put_pixels_tab[block_w == 8]);

    /* U/V */
    if (s->profile == 3) {
        /* this block only applies VP8; it is safe to check
         * only the profile, as VP7 profile <= 1 */
        uvmv.x &= ~7;
        uvmv.y &= ~7;
    }
    x_off   >>= 1;
    y_off   >>= 1;
    bx_off  >>= 1;
    by_off  >>= 1;
    width   >>= 1;
    height  >>= 1;
    block_w >>= 1;
    block_h >>= 1;
    vp8_mc_chroma(s, td, dst[1] + by_off * s->uvlinesize + bx_off,
                  dst[2] + by_off * s->uvlinesize + bx_off, ref_frame,
                  &uvmv, x_off + bx_off, y_off + by_off,
                  block_w, block_h, width, height, s->uvlinesize,
                  s->put_pixels_tab[1 + (block_w == 4)]);
}
