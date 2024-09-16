krb5_ldap_iterate_password_policy(krb5_context context, char *match_expr,
                                  void (*func)(krb5_pointer, osa_policy_ent_t),
                                  krb5_pointer func_arg)
{
    osa_policy_ent_rec          *entry=NULL;
    char                        *policy=NULL;
    krb5_error_code             st=0, tempst=0;
    LDAP                        *ld=NULL;
    LDAPMessage                 *result=NULL, *ent=NULL;
    kdb5_dal_handle             *dal_handle=NULL;
    krb5_ldap_context           *ldap_context=NULL;
    krb5_ldap_server_handle     *ldap_server_handle=NULL;

    /* Clear the global error string */
    krb5_clear_error_message(context);

    SETUP_CONTEXT();
    GET_HANDLE();

    if (ldap_context->lrparams->realmdn == NULL) {
        st = EINVAL;
        goto cleanup;
    }

    LDAP_SEARCH(ldap_context->lrparams->realmdn, LDAP_SCOPE_ONELEVEL, "(objectclass=krbpwdpolicy)", password_policy_attributes);
    for (ent=ldap_first_entry(ld, result); ent != NULL; ent=ldap_next_entry(ld, ent)) {
        krb5_boolean attr_present;

        st = krb5_ldap_get_string(ld, ent, "cn", &policy, &attr_present);
        if (st != 0)
            goto cleanup;
        if (attr_present == FALSE)
            continue;

        entry = (osa_policy_ent_t) malloc(sizeof(osa_policy_ent_rec));
        CHECK_NULL(entry);
        memset(entry, 0, sizeof(osa_policy_ent_rec));
        if ((st = populate_policy(context, ld, ent, policy, entry)) != 0)
            goto cleanup;

        (*func)(func_arg, entry);
        krb5_ldap_free_password_policy(context, entry);
        entry = NULL;

        free(policy);
        policy = NULL;
    }

cleanup:
    free(entry);
    free(policy);
    ldap_msgfree(result);
    krb5_ldap_put_handle_to_pool(ldap_context, ldap_server_handle);
    return st;
}
