asn1_decode_sequence_of_keys(krb5_data *in, ldap_seqof_key_data *out)
{
    krb5_error_code err;
    ldap_seqof_key_data *p;
    int i;

    memset(out, 0, sizeof(*out));

    /*
     * This should be pushed back into other library initialization
     * code.
     */
    err = kldap_ensure_initialized ();
    if (err)
        return err;

    err = accessor.asn1_ldap_decode_sequence_of_keys(in, &p);
    if (err)
        return err;

    /* Set kvno and key_data_ver in each key_data element. */
    for (i = 0; i < p->n_key_data; i++) {
        p->key_data[i].key_data_kvno = p->kvno;
        /* The decoder sets key_data_ver to 1 if no salt is present, but leaves
         * it at 0 if salt is present. */
        if (p->key_data[i].key_data_ver == 0)
            p->key_data[i].key_data_ver = 2;
    }

    *out = *p;
    free(p);
    return 0;
}
