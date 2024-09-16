static void fill_block16_c(uint8_t *block, uint8_t value, int line_size, int h)
{
    int i;

    for (i = 0; i < h; i++) {
        memset(block, value, 16);
        block += line_size;
    }
}
