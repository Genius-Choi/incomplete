void ff_jpeg2000_init_tier1_luts(void)
{
    int i, j;
    for (i = 0; i < 256; i++)
        for (j = 0; j < 4; j++)
            ff_jpeg2000_sigctxno_lut[i][j] = getsigctxno(i, j);
    for (i = 0; i < 16; i++)
        for (j = 0; j < 16; j++)
            ff_jpeg2000_sgnctxno_lut[i][j] =
                getsgnctxno(i + (j << 8), &ff_jpeg2000_xorbit_lut[i][j]);
}
