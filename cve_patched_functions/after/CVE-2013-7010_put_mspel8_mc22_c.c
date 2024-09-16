static void put_mspel8_mc22_c(uint8_t *dst, uint8_t *src, ptrdiff_t stride)
{
    uint8_t halfH[88];
    wmv2_mspel8_h_lowpass(halfH, src-stride, 8, stride, 11);
    wmv2_mspel8_v_lowpass(dst, halfH+8, stride, 8, 8);
}
