ptaEmpty(PTA  *pta)
{
    PROCNAME("ptaEmpty");

    if (!pta)
        return ERROR_INT("ptad not defined", procName, 1);
    pta->n = 0;
    return 0;
}
