static void put_mspel8_mc20_c(uint8_t *dst, uint8_t *src, ptrdiff_t stride)
{
    wmv2_mspel8_h_lowpass(dst, src, stride, stride, 8);
}
