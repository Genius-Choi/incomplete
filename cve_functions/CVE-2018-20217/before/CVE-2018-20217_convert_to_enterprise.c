convert_to_enterprise(krb5_context context, krb5_principal princ,
                      krb5_principal *eprinc_out)
{
    krb5_error_code code;
    char *str;

    *eprinc_out = NULL;
    code = krb5_unparse_name(context, princ, &str);
    if (code != 0)
        return code;
    code = krb5_parse_name_flags(context, str,
                                 KRB5_PRINCIPAL_PARSE_ENTERPRISE |
                                 KRB5_PRINCIPAL_PARSE_IGNORE_REALM,
                                 eprinc_out);
    krb5_free_unparsed_name(context, str);
    return code;
}
