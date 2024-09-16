static gss_name_t acceptor_name(gss_ctx_id_t context)
{
    OM_uint32 maj_stat, min_stat;
    gss_name_t name;

    maj_stat = gss_inquire_context(&min_stat, context, NULL, &name,
                                   NULL, NULL, NULL, NULL, NULL);
    if (maj_stat != GSS_S_COMPLETE)
        return NULL;
    return name;
}
