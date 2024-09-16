selSetName(SEL         *sel,
           const char  *name)
{
    PROCNAME("selSetName");

    if (!sel)
        return ERROR_INT("sel not defined", procName, 1);

    return stringReplace(&sel->name, name);
}
