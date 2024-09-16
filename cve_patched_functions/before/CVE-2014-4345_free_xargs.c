free_xargs(xargs_t xargs)
{
    if (xargs.dn)
        free (xargs.dn);
    if (xargs.linkdn)
        free(xargs.linkdn);
    if (xargs.containerdn)
        free (xargs.containerdn);
    if (xargs.tktpolicydn)
        free (xargs.tktpolicydn);
}
