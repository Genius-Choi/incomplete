static void cleanup_key_data(context, count, data)
    krb5_context   context;
    int                    count;
    krb5_key_data        * data;
{
    int i;

    for (i = 0; i < count; i++)
        krb5_free_key_data_contents(context, &data[i]);
    free(data);
}
