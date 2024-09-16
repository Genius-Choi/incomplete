pkinit_get_certs_pkcs12(krb5_context context,
                        pkinit_plg_crypto_context plg_cryptoctx,
                        pkinit_req_crypto_context req_cryptoctx,
                        pkinit_identity_opts *idopts,
                        pkinit_identity_crypto_context id_cryptoctx,
                        krb5_principal princ)
{
    krb5_error_code retval = KRB5KDC_ERR_PREAUTH_FAILED;
    X509 *x = NULL;
    PKCS12 *p12 = NULL;
    int ret;
    FILE *fp;
    EVP_PKEY *y = NULL;

    if (idopts->cert_filename == NULL) {
        pkiDebug("%s: failed to get user's cert location\n", __FUNCTION__);
        goto cleanup;
    }

    if (idopts->key_filename == NULL) {
        pkiDebug("%s: failed to get user's private key location\n", __FUNCTION__);
        goto cleanup;
    }

    fp = fopen(idopts->cert_filename, "rb");
    if (fp == NULL) {
        pkiDebug("Failed to open PKCS12 file '%s', error %d\n",
                 idopts->cert_filename, errno);
        goto cleanup;
    }
    set_cloexec_file(fp);

    p12 = d2i_PKCS12_fp(fp, NULL);
    fclose(fp);
    if (p12 == NULL) {
        pkiDebug("Failed to decode PKCS12 file '%s' contents\n",
                 idopts->cert_filename);
        goto cleanup;
    }
    /*
     * Try parsing with no pass phrase first.  If that fails,
     * prompt for the pass phrase and try again.
     */
    ret = PKCS12_parse(p12, NULL, &y, &x, NULL);
    if (ret == 0) {
        krb5_data rdat;
        krb5_prompt kprompt;
        krb5_prompt_type prompt_type;
        int r = 0;
        char prompt_string[128];
        char prompt_reply[128];
        char *prompt_prefix = _("Pass phrase for");

        pkiDebug("Initial PKCS12_parse with no password failed\n");

        memset(prompt_reply, '\0', sizeof(prompt_reply));
        rdat.data = prompt_reply;
        rdat.length = sizeof(prompt_reply);

        r = snprintf(prompt_string, sizeof(prompt_string), "%s %s",
                     prompt_prefix, idopts->cert_filename);
        if (r >= (int) sizeof(prompt_string)) {
            pkiDebug("Prompt string, '%s %s', is too long!\n",
                     prompt_prefix, idopts->cert_filename);
            goto cleanup;
        }
        kprompt.prompt = prompt_string;
        kprompt.hidden = 1;
        kprompt.reply = &rdat;
        prompt_type = KRB5_PROMPT_TYPE_PREAUTH;

        /* PROMPTER_INVOCATION */
        k5int_set_prompt_types(context, &prompt_type);
        r = (*id_cryptoctx->prompter)(context, id_cryptoctx->prompter_data,
                                      NULL, NULL, 1, &kprompt);
        k5int_set_prompt_types(context, 0);

        ret = PKCS12_parse(p12, rdat.data, &y, &x, NULL);
        if (ret == 0) {
            pkiDebug("Seconde PKCS12_parse with password failed\n");
            goto cleanup;
        }
    }
    id_cryptoctx->creds[0] = malloc(sizeof(struct _pkinit_cred_info));
    if (id_cryptoctx->creds[0] == NULL)
        goto cleanup;
    id_cryptoctx->creds[0]->name =
        reassemble_pkcs12_name(idopts->cert_filename);
    id_cryptoctx->creds[0]->cert = x;
#ifndef WITHOUT_PKCS11
    id_cryptoctx->creds[0]->cert_id = NULL;
    id_cryptoctx->creds[0]->cert_id_len = 0;
#endif
    id_cryptoctx->creds[0]->key = y;
    id_cryptoctx->creds[1] = NULL;

    retval = 0;

cleanup:
    if (p12)
        PKCS12_free(p12);
    if (retval) {
        if (x != NULL)
            X509_free(x);
        if (y != NULL)
            EVP_PKEY_free(y);
    }
    return retval;
}
