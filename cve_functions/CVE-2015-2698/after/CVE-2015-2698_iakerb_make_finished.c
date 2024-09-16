iakerb_make_finished(krb5_context context,
                     krb5_key key,
                     const krb5_data *conv,
                     krb5_data **finished)
{
    krb5_error_code code;
    krb5_iakerb_finished iaf;

    *finished = NULL;

    memset(&iaf, 0, sizeof(iaf));

    if (key == NULL)
        return KRB5KDC_ERR_NULL_KEY;

    code = krb5_k_make_checksum(context, 0, key, KRB5_KEYUSAGE_IAKERB_FINISHED,
                                conv, &iaf.checksum);
    if (code != 0)
        return code;

    code = encode_krb5_iakerb_finished(&iaf, finished);

    krb5_free_checksum_contents(context, &iaf.checksum);

    return code;
}
