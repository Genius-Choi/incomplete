krb5_ldap_delete_password_policy(krb5_context context, char *policy)
{
    int                         mask = 0;
    char                        *policy_dn = NULL, *class[] = {"krbpwdpolicy", NULL};
    krb5_error_code             st=0;
    LDAP                        *ld=NULL;
    kdb5_dal_handle             *dal_handle=NULL;
    krb5_ldap_context           *ldap_context=NULL;
    krb5_ldap_server_handle     *ldap_server_handle=NULL;

    /* Clear the global error string */
    krb5_clear_error_message(context);

    /* validate the input parameters */
    if (policy == NULL)
        return EINVAL;

    SETUP_CONTEXT();
    GET_HANDLE();

    st = krb5_ldap_name_to_policydn (context, policy, &policy_dn);
    if (st != 0)
        goto cleanup;

    /* Ensure that the object is a password policy */
    if ((st=checkattributevalue(ld, policy_dn, "objectclass", class, &mask)) != 0)
        goto cleanup;

    if (mask == 0) {
        st = KRB5_KDB_NOENTRY;
        goto cleanup;
    }

    if ((st=ldap_delete_ext_s(ld, policy_dn, NULL, NULL)) != LDAP_SUCCESS) {
        st = set_ldap_error (context, st, OP_DEL);
        goto cleanup;
    }

cleanup:
    krb5_ldap_put_handle_to_pool(ldap_context, ldap_server_handle);
    free(policy_dn);

    return st;
}
