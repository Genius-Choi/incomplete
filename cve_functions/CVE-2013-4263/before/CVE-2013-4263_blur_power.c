static inline void blur_power(uint8_t *dst, int dst_step, const uint8_t *src, int src_step,
                              int len, int radius, int power, uint8_t *temp[2])
{
    uint8_t *a = temp[0], *b = temp[1];

    if (radius && power) {
        blur(a, 1, src, src_step, len, radius);
        for (; power > 2; power--) {
            uint8_t *c;
            blur(b, 1, a, 1, len, radius);
            c = a; a = b; b = c;
        }
        if (power > 1) {
            blur(dst, dst_step, a, 1, len, radius);
        } else {
            int i;
            for (i = 0; i < len; i++)
                dst[i*dst_step] = a[i];
        }
    } else {
        int i;
        for (i = 0; i < len; i++)
            dst[i*dst_step] = src[i*src_step];
    }
}
