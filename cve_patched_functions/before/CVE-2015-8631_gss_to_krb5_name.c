static int gss_to_krb5_name(kadm5_server_handle_t handle,
                            gss_name_t gss_name, krb5_principal *princ)
{
    OM_uint32 minor_stat;
    gss_buffer_desc gss_str;
    int success;
    char *s;

    if (gss_name_to_string(gss_name, &gss_str) != 0)
        return 0;
    if (asprintf(&s, "%.*s", (int)gss_str.length, (char *)gss_str.value) < 0) {
        gss_release_buffer(&minor_stat, &gss_str);
        return 0;
    }
    success = (krb5_parse_name(handle->context, s, princ) == 0);
    free(s);
    gss_release_buffer(&minor_stat, &gss_str);
    return success;
}
