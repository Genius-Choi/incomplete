krb5_gss_localname(OM_uint32 *minor,
                   const gss_name_t pname,
                   const gss_const_OID mech_type,
                   gss_buffer_t localname)
{
    krb5_context context;
    krb5_error_code code;
    krb5_gss_name_t kname;
    char lname[BUFSIZ];

    code = krb5_gss_init_context(&context);
    if (code != 0) {
        *minor = code;
        return GSS_S_FAILURE;
    }

    kname = (krb5_gss_name_t)pname;

    code = krb5_aname_to_localname(context, kname->princ,
                                   sizeof(lname), lname);
    if (code != 0) {
        *minor = KRB5_NO_LOCALNAME;
        krb5_free_context(context);
        return GSS_S_FAILURE;
    }


    krb5_free_context(context);
    localname->value = gssalloc_strdup(lname);
    localname->length = strlen(lname);

    return (code == 0) ? GSS_S_COMPLETE : GSS_S_FAILURE;
}
