static int cmp_gss_names(gss_name_t n1, gss_name_t n2)
{
    OM_uint32 emin;
    int equal;

    if (GSS_ERROR(gss_compare_name(&emin, n1, n2, &equal)))
        return(0);

    return(equal);
}
