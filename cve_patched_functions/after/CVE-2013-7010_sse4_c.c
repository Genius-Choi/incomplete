static int sse4_c(void *v, uint8_t * pix1, uint8_t * pix2, int line_size, int h)
{
    int s, i;
    uint32_t *sq = ff_squareTbl + 256;

    s = 0;
    for (i = 0; i < h; i++) {
        s += sq[pix1[0] - pix2[0]];
        s += sq[pix1[1] - pix2[1]];
        s += sq[pix1[2] - pix2[2]];
        s += sq[pix1[3] - pix2[3]];
        pix1 += line_size;
        pix2 += line_size;
    }
    return s;
}
