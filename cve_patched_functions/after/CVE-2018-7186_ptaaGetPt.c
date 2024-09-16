ptaaGetPt(PTAA       *ptaa,
           l_int32     ipta,
           l_int32     jpt,
           l_float32  *px,
           l_float32  *py)
{
PTA  *pta;

    PROCNAME("ptaaGetPt");

    if (px) *px = 0;
    if (py) *py = 0;
    if (!ptaa)
        return ERROR_INT("ptaa not defined", procName, 1);
    if (ipta < 0 || ipta >= ptaa->n)
        return ERROR_INT("index ipta not valid", procName, 1);

    pta = ptaaGetPta(ptaa, ipta, L_CLONE);
    if (jpt < 0 || jpt >= pta->n) {
        ptaDestroy(&pta);
        return ERROR_INT("index jpt not valid", procName, 1);
    }

    ptaGetPt(pta, jpt, px, py);
    ptaDestroy(&pta);
    return 0;
}
