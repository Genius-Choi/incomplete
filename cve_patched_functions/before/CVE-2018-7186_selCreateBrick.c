selCreateBrick(l_int32  h,
               l_int32  w,
               l_int32  cy,
               l_int32  cx,
               l_int32  type)
{
l_int32  i, j;
SEL     *sel;

    PROCNAME("selCreateBrick");

    if (h <= 0 || w <= 0)
        return (SEL *)ERROR_PTR("h and w must both be > 0", procName, NULL);
    if (type != SEL_HIT && type != SEL_MISS && type != SEL_DONT_CARE)
        return (SEL *)ERROR_PTR("invalid sel element type", procName, NULL);

    if ((sel = selCreate(h, w, NULL)) == NULL)
        return (SEL *)ERROR_PTR("sel not made", procName, NULL);
    selSetOrigin(sel, cy, cx);
    for (i = 0; i < h; i++)
        for (j = 0; j < w; j++)
            sel->data[i][j] = type;

    return sel;
}
