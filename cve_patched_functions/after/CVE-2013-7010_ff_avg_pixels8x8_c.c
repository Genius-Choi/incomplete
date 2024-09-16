void ff_avg_pixels8x8_c(uint8_t *dst, uint8_t *src, ptrdiff_t stride)
{
    avg_pixels8_8_c(dst, src, stride, 8);
}
