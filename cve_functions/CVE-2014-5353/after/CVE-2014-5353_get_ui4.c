get_ui4(LDAP *ld, LDAPMessage *ent, char *name, krb5_ui_4 *out)
{
    int val;

    krb5_ldap_get_value(ld, ent, name, &val);
    *out = val;
}
