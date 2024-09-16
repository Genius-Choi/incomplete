static void put_mspel8_mc02_c(uint8_t *dst, uint8_t *src, ptrdiff_t stride)
{
    wmv2_mspel8_v_lowpass(dst, src, stride, stride, 8);
}
