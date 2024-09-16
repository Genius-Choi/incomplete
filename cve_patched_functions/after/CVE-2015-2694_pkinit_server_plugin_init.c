pkinit_server_plugin_init(krb5_context context,
                          krb5_kdcpreauth_moddata *moddata_out,
                          const char **realmnames)
{
    krb5_error_code retval = ENOMEM;
    pkinit_kdc_context plgctx, *realm_contexts = NULL;
    size_t  i, j;
    size_t numrealms;

    retval = pkinit_accessor_init();
    if (retval)
        return retval;

    /* Determine how many realms we may need to support */
    for (i = 0; realmnames[i] != NULL; i++) {};
    numrealms = i;

    realm_contexts = calloc(numrealms+1, sizeof(pkinit_kdc_context));
    if (realm_contexts == NULL)
        return ENOMEM;

    for (i = 0, j = 0; i < numrealms; i++) {
        pkiDebug("%s: processing realm '%s'\n", __FUNCTION__, realmnames[i]);
        retval = pkinit_server_plugin_init_realm(context, realmnames[i], &plgctx);
        if (retval == 0 && plgctx != NULL)
            realm_contexts[j++] = plgctx;
    }

    if (j == 0) {
        retval = EINVAL;
        krb5_set_error_message(context, retval,
                               _("No realms configured correctly for pkinit "
                                 "support"));
        goto errout;
    }

    *moddata_out = (krb5_kdcpreauth_moddata)realm_contexts;
    retval = 0;
    pkiDebug("%s: returning context at %p\n", __FUNCTION__, realm_contexts);

errout:
    if (retval) {
        pkinit_server_plugin_fini(context,
                                  (krb5_kdcpreauth_moddata)realm_contexts);
    }

    return retval;
}
