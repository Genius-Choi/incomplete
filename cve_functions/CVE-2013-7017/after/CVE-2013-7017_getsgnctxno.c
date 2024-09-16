static int getsgnctxno(int flag, uint8_t *xorbit)
{
    int vcontrib, hcontrib;

    hcontrib = contribtab[flag & JPEG2000_T1_SIG_E ? flag & JPEG2000_T1_SGN_E ? 1 : 2 : 0]
                         [flag & JPEG2000_T1_SIG_W ? flag & JPEG2000_T1_SGN_W ? 1 : 2 : 0] + 1;
    vcontrib = contribtab[flag & JPEG2000_T1_SIG_S ? flag & JPEG2000_T1_SGN_S ? 1 : 2 : 0]
                         [flag & JPEG2000_T1_SIG_N ? flag & JPEG2000_T1_SGN_N ? 1 : 2 : 0] + 1;
    *xorbit = xorbittab[hcontrib][vcontrib];

    return ctxlbltab[hcontrib][vcontrib];
}
