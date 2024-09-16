static void put_mspel8_mc10_c(uint8_t *dst, uint8_t *src, ptrdiff_t stride)
{
    uint8_t half[64];
    wmv2_mspel8_h_lowpass(half, src, 8, stride, 8);
    put_pixels8_l2_8(dst, src, half, stride, stride, 8, 8);
}
