krb5_get_credentials_for_user(krb5_context context, krb5_flags options,
                              krb5_ccache ccache, krb5_creds *in_creds,
                              krb5_data *subject_cert,
                              krb5_creds **out_creds)
{
    krb5_error_code code;
    krb5_principal realm = NULL;

    *out_creds = NULL;

    if (options & KRB5_GC_CONSTRAINED_DELEGATION) {
        code = EINVAL;
        goto cleanup;
    }

    if (in_creds->client != NULL) {
        /* Uncanonicalised check */
        code = krb5_get_credentials(context, options | KRB5_GC_CACHED,
                                    ccache, in_creds, out_creds);
        if (code != KRB5_CC_NOTFOUND && code != KRB5_CC_NOT_KTYPE)
            goto cleanup;

        if ((options & KRB5_GC_CACHED) && !(options & KRB5_GC_CANONICALIZE))
            goto cleanup;
    }

    code = s4u_identify_user(context, in_creds, subject_cert, &realm);
    if (code != 0)
        goto cleanup;

    if (in_creds->client != NULL &&
        in_creds->client->type == KRB5_NT_ENTERPRISE_PRINCIPAL) {
        /* Post-canonicalisation check for enterprise principals */
        krb5_creds mcreds = *in_creds;
        mcreds.client = realm;
        code = krb5_get_credentials(context, options | KRB5_GC_CACHED,
                                    ccache, &mcreds, out_creds);
        if ((code != KRB5_CC_NOTFOUND && code != KRB5_CC_NOT_KTYPE)
            || (options & KRB5_GC_CACHED))
            goto cleanup;
    }

    code = krb5_get_self_cred_from_kdc(context, options, ccache, in_creds,
                                       subject_cert, &realm->realm, out_creds);
    if (code != 0)
        goto cleanup;

    assert(*out_creds != NULL);

    if ((options & KRB5_GC_NO_STORE) == 0) {
        code = krb5_cc_store_cred(context, ccache, *out_creds);
        if (code != 0)
            goto cleanup;
    }

cleanup:
    if (code != 0 && *out_creds != NULL) {
        krb5_free_creds(context, *out_creds);
        *out_creds = NULL;
    }

    krb5_free_principal(context, realm);

    return code;
}
