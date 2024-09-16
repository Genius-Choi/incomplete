pkinit_create_sequence_of_principal_identifiers(
    krb5_context context,
    pkinit_plg_crypto_context plg_cryptoctx,
    pkinit_req_crypto_context req_cryptoctx,
    pkinit_identity_crypto_context id_cryptoctx,
    int type,
    krb5_pa_data ***e_data_out)
{
    krb5_error_code retval = KRB5KRB_ERR_GENERIC;
    krb5_external_principal_identifier **krb5_trusted_certifiers = NULL;
    krb5_data *td_certifiers = NULL;
    krb5_pa_data **pa_data = NULL;

    switch(type) {
    case TD_TRUSTED_CERTIFIERS:
        retval = create_krb5_trustedCertifiers(context, plg_cryptoctx,
                                               req_cryptoctx, id_cryptoctx, &krb5_trusted_certifiers);
        if (retval) {
            pkiDebug("create_krb5_trustedCertifiers failed\n");
            goto cleanup;
        }
        break;
    case TD_INVALID_CERTIFICATES:
        retval = create_krb5_invalidCertificates(context, plg_cryptoctx,
                                                 req_cryptoctx, id_cryptoctx, &krb5_trusted_certifiers);
        if (retval) {
            pkiDebug("create_krb5_invalidCertificates failed\n");
            goto cleanup;
        }
        break;
    default:
        retval = -1;
        goto cleanup;
    }

    retval = k5int_encode_krb5_td_trusted_certifiers((const krb5_external_principal_identifier **)krb5_trusted_certifiers, &td_certifiers);
    if (retval) {
        pkiDebug("encode_krb5_td_trusted_certifiers failed\n");
        goto cleanup;
    }
#ifdef DEBUG_ASN1
    print_buffer_bin((unsigned char *)td_certifiers->data,
                     td_certifiers->length, "/tmp/kdc_td_certifiers");
#endif
    pa_data = malloc(2 * sizeof(krb5_pa_data *));
    if (pa_data == NULL) {
        retval = ENOMEM;
        goto cleanup;
    }
    pa_data[1] = NULL;
    pa_data[0] = malloc(sizeof(krb5_pa_data));
    if (pa_data[0] == NULL) {
        free(pa_data);
        retval = ENOMEM;
        goto cleanup;
    }
    pa_data[0]->pa_type = type;
    pa_data[0]->length = td_certifiers->length;
    pa_data[0]->contents = (krb5_octet *)td_certifiers->data;
    *e_data_out = pa_data;
    retval = 0;

cleanup:
    if (krb5_trusted_certifiers != NULL)
        free_krb5_external_principal_identifier(&krb5_trusted_certifiers);
    free(td_certifiers);
    return retval;
}
