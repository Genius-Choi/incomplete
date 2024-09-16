dbentry_supports_enctype(kdc_realm_t *kdc_active_realm, krb5_db_entry *server,
                         krb5_enctype enctype)
{
    krb5_error_code     retval;
    krb5_key_data       *datap;
    char                *etypes_str = NULL;
    krb5_enctype        default_enctypes[1] = { 0 };
    krb5_enctype        *etypes = NULL;
    krb5_boolean        in_list;

    /* Look up the supported session key enctypes list in the KDB. */
    retval = krb5_dbe_get_string(kdc_context, server,
                                 KRB5_KDB_SK_SESSION_ENCTYPES,
                                 &etypes_str);
    if (retval == 0 && etypes_str != NULL && *etypes_str != '\0') {
        /* Pass a fake profile key for tracing of unrecognized tokens. */
        retval = krb5int_parse_enctype_list(kdc_context, "KDB-session_etypes",
                                            etypes_str, default_enctypes,
                                            &etypes);
        if (retval == 0 && etypes != NULL && etypes[0]) {
            in_list = k5_etypes_contains(etypes, enctype);
            free(etypes_str);
            free(etypes);
            return in_list;
        }
        /* Fall through on error or empty list */
    }
    free(etypes_str);
    free(etypes);

    /* If configured to, assume every server without a session_enctypes
     * attribute supports DES_CBC_CRC. */
    if (kdc_active_realm->realm_assume_des_crc_sess &&
        enctype == ENCTYPE_DES_CBC_CRC)
        return TRUE;

    /* Due to an ancient interop problem, assume nothing supports des-cbc-md5
     * unless there's a session_enctypes explicitly saying that it does. */
    if (enctype == ENCTYPE_DES_CBC_MD5)
        return FALSE;

    /* Assume the server supports any enctype it has a long-term key for. */
    return !krb5_dbe_find_enctype(kdc_context, server, enctype, -1, 0, &datap);
}
