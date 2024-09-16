find_server_key(krb5_context context,
                krb5_db_entry *server, krb5_enctype enctype, krb5_kvno kvno,
                krb5_keyblock **key_out, krb5_kvno *kvno_out)
{
    krb5_error_code       retval;
    krb5_key_data       * server_key;
    krb5_keyblock       * key;

    *key_out = NULL;
    retval = krb5_dbe_find_enctype(context, server, enctype, -1,
                                   kvno ? (krb5_int32)kvno : -1, &server_key);
    if (retval)
        return retval;
    if (!server_key)
        return KRB5KDC_ERR_S_PRINCIPAL_UNKNOWN;
    if ((key = (krb5_keyblock *)malloc(sizeof *key)) == NULL)
        return ENOMEM;
    retval = krb5_dbe_decrypt_key_data(context, NULL, server_key,
                                       key, NULL);
    if (retval)
        goto errout;
    if (enctype != -1) {
        krb5_boolean similar;
        retval = krb5_c_enctype_compare(context, enctype, key->enctype,
                                        &similar);
        if (retval)
            goto errout;
        if (!similar) {
            retval = KRB5_KDB_NO_PERMITTED_KEY;
            goto errout;
        }
        key->enctype = enctype;
    }
    *key_out = key;
    key = NULL;
    if (kvno_out)
        *kvno_out = server_key->key_data_kvno;
errout:
    krb5_free_keyblock(context, key);
    return retval;
}
