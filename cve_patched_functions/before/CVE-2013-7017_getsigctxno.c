static int getsigctxno(int flag, int bandno)
{
    int h, v, d;

    h = ((flag & JPEG2000_T1_SIG_E)  ? 1 : 0) +
        ((flag & JPEG2000_T1_SIG_W)  ? 1 : 0);
    v = ((flag & JPEG2000_T1_SIG_N)  ? 1 : 0) +
        ((flag & JPEG2000_T1_SIG_S)  ? 1 : 0);
    d = ((flag & JPEG2000_T1_SIG_NE) ? 1 : 0) +
        ((flag & JPEG2000_T1_SIG_NW) ? 1 : 0) +
        ((flag & JPEG2000_T1_SIG_SE) ? 1 : 0) +
        ((flag & JPEG2000_T1_SIG_SW) ? 1 : 0);

    if (bandno < 3) {
        if (bandno == 1)
            FFSWAP(int, h, v);
        if (h == 2) return 8;
        if (h == 1) {
            if (v >= 1) return 7;
            if (d >= 1) return 6;
            return 5;
        }
        if (v == 2) return 4;
        if (v == 1) return 3;
        if (d >= 2) return 2;
        if (d == 1) return 1;
    } else {
        if (d >= 3) return 8;
        if (d == 2) {
            if (h+v >= 1) return 7;
            return 6;
        }
        if (d == 1) {
            if (h+v >= 2) return 5;
            if (h+v == 1) return 4;
            return 3;
        }
        if (h+v >= 2) return 2;
        if (h+v == 1) return 1;
    }
    return 0;
}
