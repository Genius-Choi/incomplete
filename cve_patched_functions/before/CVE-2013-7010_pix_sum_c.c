static int pix_sum_c(uint8_t * pix, int line_size)
{
    int s, i, j;

    s = 0;
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j += 8) {
            s += pix[0];
            s += pix[1];
            s += pix[2];
            s += pix[3];
            s += pix[4];
            s += pix[5];
            s += pix[6];
            s += pix[7];
            pix += 8;
        }
        pix += line_size - 16;
    }
    return s;
}
