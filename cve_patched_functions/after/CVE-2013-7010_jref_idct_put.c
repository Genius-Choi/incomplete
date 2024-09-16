static void jref_idct_put(uint8_t *dest, int line_size, int16_t *block)
{
    ff_j_rev_dct (block);
    put_pixels_clamped_c(block, dest, line_size);
}
