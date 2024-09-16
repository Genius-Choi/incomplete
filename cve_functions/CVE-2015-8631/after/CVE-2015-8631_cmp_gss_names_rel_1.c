static int cmp_gss_names_rel_1(gss_name_t n1, gss_name_t n2)
{
    OM_uint32 min_stat;
    int ret;

    ret = cmp_gss_names(n1, n2);
    if (n1) (void) gss_release_name(&min_stat, &n1);
    return ret;
}
