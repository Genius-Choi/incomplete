free_ldap_seqof_key_data(ldap_seqof_key_data *keysets, krb5_int16 n_keysets)
{
    int i;

    if (keysets == NULL)
        return;

    for (i = 0; i < n_keysets; i++)
        k5_free_key_data(keysets[i].n_key_data, keysets[i].key_data);
    free(keysets);
}
