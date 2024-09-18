selGetParameters(SEL      *sel,
                 l_int32  *psy,
                 l_int32  *psx,
                 l_int32  *pcy,
                 l_int32  *pcx)
{
    PROCNAME("selGetParameters");

    if (psy) *psy = 0;
    if (psx) *psx = 0;
    if (pcy) *pcy = 0;
    if (pcx) *pcx = 0;
    if (!sel)
        return ERROR_INT("sel not defined", procName, 1);
    if (psy) *psy = sel->sy;
    if (psx) *psx = sel->sx;
    if (pcy) *pcy = sel->cy;
    if (pcx) *pcx = sel->cx;
    return 0;
}
