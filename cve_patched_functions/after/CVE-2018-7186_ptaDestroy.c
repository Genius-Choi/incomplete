ptaDestroy(PTA  **ppta)
{
PTA  *pta;

    PROCNAME("ptaDestroy");

    if (ppta == NULL) {
        L_WARNING("ptr address is NULL!\n", procName);
        return;
    }

    if ((pta = *ppta) == NULL)
        return;

    ptaChangeRefcount(pta, -1);
    if (ptaGetRefcount(pta) <= 0) {
        LEPT_FREE(pta->x);
        LEPT_FREE(pta->y);
        LEPT_FREE(pta);
    }

    *ppta = NULL;
    return;
}
