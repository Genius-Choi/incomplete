make_ks_from_key_data(krb5_context context, kadm5_key_data *key_data,
                      int n_key_data, krb5_key_salt_tuple **out)
{
    int i;
    krb5_key_salt_tuple *ks;

    *out = NULL;

    ks = calloc(n_key_data, sizeof(*ks));
    if (ks == NULL)
        return ENOMEM;

    for (i = 0; i < n_key_data; i++) {
        ks[i].ks_enctype = key_data[i].key.enctype;
        ks[i].ks_salttype = key_data[i].salt.type;
    }
    *out = ks;
    return 0;
}
