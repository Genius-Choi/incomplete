gss_krb5int_inq_session_key(
    OM_uint32 *minor_status,
    const gss_ctx_id_t context_handle,
    const gss_OID desired_object,
    gss_buffer_set_t *data_set)
{
    krb5_gss_ctx_id_rec *ctx;
    krb5_key key;
    gss_buffer_desc keyvalue, keyinfo;
    OM_uint32 major_status, minor;
    unsigned char oid_buf[GSS_KRB5_SESSION_KEY_ENCTYPE_OID_LENGTH + 6];
    gss_OID_desc oid;

    ctx = (krb5_gss_ctx_id_rec *) context_handle;
    key = ctx->have_acceptor_subkey ? ctx->acceptor_subkey : ctx->subkey;

    keyvalue.value = key->keyblock.contents;
    keyvalue.length = key->keyblock.length;

    major_status = generic_gss_add_buffer_set_member(minor_status, &keyvalue, data_set);
    if (GSS_ERROR(major_status))
        goto cleanup;

    oid.elements = oid_buf;
    oid.length = sizeof(oid_buf);

    major_status = generic_gss_oid_compose(minor_status,
                                           GSS_KRB5_SESSION_KEY_ENCTYPE_OID,
                                           GSS_KRB5_SESSION_KEY_ENCTYPE_OID_LENGTH,
                                           key->keyblock.enctype,
                                           &oid);
    if (GSS_ERROR(major_status))
        goto cleanup;

    keyinfo.value = oid.elements;
    keyinfo.length = oid.length;

    major_status = generic_gss_add_buffer_set_member(minor_status, &keyinfo, data_set);
    if (GSS_ERROR(major_status))
        goto cleanup;

    return GSS_S_COMPLETE;

cleanup:
    if (*data_set != GSS_C_NO_BUFFER_SET) {
        if ((*data_set)->count != 0)
            memset((*data_set)->elements[0].value, 0, (*data_set)->elements[0].length);
        gss_release_buffer_set(&minor, data_set);
    }

    return major_status;
}
