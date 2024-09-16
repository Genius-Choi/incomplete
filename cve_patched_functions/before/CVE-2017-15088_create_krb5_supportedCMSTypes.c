create_krb5_supportedCMSTypes(krb5_context context,
                              pkinit_plg_crypto_context plg_cryptoctx,
                              pkinit_req_crypto_context req_cryptoctx,
                              pkinit_identity_crypto_context id_cryptoctx,
                              krb5_algorithm_identifier ***oids)
{

    krb5_error_code retval = ENOMEM;
    krb5_algorithm_identifier **loids = NULL;
    krb5_data des3oid = {0, 8, "\x2A\x86\x48\x86\xF7\x0D\x03\x07" };

    *oids = NULL;
    loids = malloc(2 * sizeof(krb5_algorithm_identifier *));
    if (loids == NULL)
        goto cleanup;
    loids[1] = NULL;
    loids[0] = malloc(sizeof(krb5_algorithm_identifier));
    if (loids[0] == NULL) {
        free(loids);
        goto cleanup;
    }
    retval = pkinit_copy_krb5_data(&loids[0]->algorithm, &des3oid);
    if (retval) {
        free(loids[0]);
        free(loids);
        goto cleanup;
    }
    loids[0]->parameters.length = 0;
    loids[0]->parameters.data = NULL;

    *oids = loids;
    retval = 0;
cleanup:

    return retval;
}
