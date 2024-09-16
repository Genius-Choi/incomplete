static void jref_idct_add(uint8_t *dest, int line_size, int16_t *block)
{
    ff_j_rev_dct (block);
    add_pixels_clamped_c(block, dest, line_size);
}
