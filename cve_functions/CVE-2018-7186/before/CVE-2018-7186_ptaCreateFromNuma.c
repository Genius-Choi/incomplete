ptaCreateFromNuma(NUMA  *nax,
                  NUMA  *nay)
{
l_int32    i, n;
l_float32  startx, delx, xval, yval;
PTA       *pta;

    PROCNAME("ptaCreateFromNuma");

    if (!nay)
        return (PTA *)ERROR_PTR("nay not defined", procName, NULL);
    n = numaGetCount(nay);
    if (nax && numaGetCount(nax) != n)
        return (PTA *)ERROR_PTR("nax and nay sizes differ", procName, NULL);

    pta = ptaCreate(n);
    numaGetParameters(nay, &startx, &delx);
    for (i = 0; i < n; i++) {
        if (nax)
            numaGetFValue(nax, i, &xval);
        else  /* use implicit x values from nay */
            xval = startx + i * delx;
        numaGetFValue(nay, i, &yval);
        ptaAddPt(pta, xval, yval);
    }

    return pta;
}
