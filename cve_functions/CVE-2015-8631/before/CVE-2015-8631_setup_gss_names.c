int setup_gss_names(struct svc_req *rqstp,
                    gss_buffer_desc *client_name,
                    gss_buffer_desc *server_name)
{
    OM_uint32 maj_stat, min_stat;
    gss_name_t server_gss_name;

    if (gss_name_to_string(rqst2name(rqstp), client_name) != 0)
        return -1;
    maj_stat = gss_inquire_context(&min_stat, rqstp->rq_svccred, NULL,
                                   &server_gss_name, NULL, NULL, NULL,
                                   NULL, NULL);
    if (maj_stat != GSS_S_COMPLETE) {
        gss_release_buffer(&min_stat, client_name);
        gss_release_name(&min_stat, &server_gss_name);
        return -1;
    }
    if (gss_name_to_string(server_gss_name, server_name) != 0) {
        gss_release_buffer(&min_stat, client_name);
        gss_release_name(&min_stat, &server_gss_name);
        return -1;
    }
    gss_release_name(&min_stat, &server_gss_name);
    return 0;
}
