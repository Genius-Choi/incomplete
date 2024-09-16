krb5_ldap_create_password_policy(krb5_context context, osa_policy_ent_t policy)
{
    krb5_error_code             st=0;
    LDAP                        *ld=NULL;
    LDAPMod                     **mods={NULL};
    kdb5_dal_handle             *dal_handle=NULL;
    krb5_ldap_context           *ldap_context=NULL;
    krb5_ldap_server_handle     *ldap_server_handle=NULL;
    char                        *strval[2]={NULL}, *policy_dn=NULL;

    /* Clear the global error string */
    krb5_clear_error_message(context);

    /* validate the input parameters */
    if (policy == NULL || policy->name == NULL)
        return EINVAL;

    SETUP_CONTEXT();
    GET_HANDLE();

    st = krb5_ldap_name_to_policydn (context, policy->name, &policy_dn);
    if (st != 0)
        goto cleanup;

    strval[0] = policy->name;
    if ((st=krb5_add_str_mem_ldap_mod(&mods, "cn", LDAP_MOD_ADD, strval)) != 0)
        goto cleanup;

    strval[0] = "krbPwdPolicy";
    if ((st=krb5_add_str_mem_ldap_mod(&mods, "objectclass", LDAP_MOD_ADD, strval)) != 0)
        goto cleanup;

    st = add_policy_mods(context, &mods, policy, LDAP_MOD_ADD);
    if (st)
        goto cleanup;

    /* password policy object creation */
    if ((st=ldap_add_ext_s(ld, policy_dn, mods, NULL, NULL)) != LDAP_SUCCESS) {
        st = set_ldap_error (context, st, OP_ADD);
        goto cleanup;
    }

cleanup:
    free(policy_dn);
    ldap_mods_free(mods, 1);
    krb5_ldap_put_handle_to_pool(ldap_context, ldap_server_handle);
    return(st);
}
