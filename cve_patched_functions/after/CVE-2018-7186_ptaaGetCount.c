ptaaGetCount(PTAA  *ptaa)
{
    PROCNAME("ptaaGetCount");

    if (!ptaa)
        return ERROR_INT("ptaa not defined", procName, 0);

    return ptaa->n;
}
