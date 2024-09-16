selaGetSelnames(SELA  *sela)
{
char    *selname;
l_int32  i, n;
SEL     *sel;
SARRAY  *sa;

    PROCNAME("selaGetSelnames");

    if (!sela)
        return (SARRAY *)ERROR_PTR("sela not defined", procName, NULL);
    if ((n = selaGetCount(sela)) == 0)
        return (SARRAY *)ERROR_PTR("no sels in sela", procName, NULL);

    if ((sa = sarrayCreate(n)) == NULL)
        return (SARRAY *)ERROR_PTR("sa not made", procName, NULL);
    for (i = 0; i < n; i++) {
        sel = selaGetSel(sela, i);
        selname = selGetName(sel);
        sarrayAddString(sa, selname, L_COPY);
    }

    return sa;
}
