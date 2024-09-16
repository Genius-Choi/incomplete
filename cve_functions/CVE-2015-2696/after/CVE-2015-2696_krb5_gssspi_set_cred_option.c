krb5_gssspi_set_cred_option(OM_uint32 *minor_status,
                            gss_cred_id_t *cred_handle,
                            const gss_OID desired_object,
                            const gss_buffer_t value)
{
    OM_uint32 major_status = GSS_S_FAILURE;
    size_t i;

    if (minor_status == NULL)
        return GSS_S_CALL_INACCESSIBLE_WRITE;

    if (cred_handle == NULL)
        return GSS_S_CALL_INACCESSIBLE_WRITE;

    *minor_status = 0;

    if (desired_object == GSS_C_NO_OID)
        return GSS_S_CALL_INACCESSIBLE_READ;

    if (*cred_handle != GSS_C_NO_CREDENTIAL) {
        major_status = krb5_gss_validate_cred(minor_status, *cred_handle);
        if (GSS_ERROR(major_status))
            return major_status;
    }

    for (i = 0; i < sizeof(krb5_gssspi_set_cred_option_ops)/
             sizeof(krb5_gssspi_set_cred_option_ops[0]); i++) {
        if (g_OID_prefix_equal(desired_object, &krb5_gssspi_set_cred_option_ops[i].oid)) {
            return (*krb5_gssspi_set_cred_option_ops[i].func)(minor_status,
                                                              cred_handle,
                                                              desired_object,
                                                              value);
        }
    }

    *minor_status = EINVAL;

    return GSS_S_UNAVAILABLE;
}
