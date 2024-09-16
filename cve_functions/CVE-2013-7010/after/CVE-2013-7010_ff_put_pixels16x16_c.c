void ff_put_pixels16x16_c(uint8_t *dst, uint8_t *src, ptrdiff_t stride)
{
    put_pixels16_8_c(dst, src, stride, 16);
}
