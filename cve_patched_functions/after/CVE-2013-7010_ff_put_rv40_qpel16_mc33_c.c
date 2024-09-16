void ff_put_rv40_qpel16_mc33_c(uint8_t *dst, uint8_t *src, ptrdiff_t stride)
{
    put_pixels16_xy2_8_c(dst, src, stride, 16);
}
