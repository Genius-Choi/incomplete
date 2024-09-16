berval2tl_data(struct berval *in, krb5_tl_data **out)
{
    *out = (krb5_tl_data *) malloc (sizeof (krb5_tl_data));
    if (*out == NULL)
        return ENOMEM;

    (*out)->tl_data_length = in->bv_len - 2;
    (*out)->tl_data_contents =  (krb5_octet *) malloc
        ((*out)->tl_data_length * sizeof (krb5_octet));
    if ((*out)->tl_data_contents == NULL) {
        free (*out);
        return ENOMEM;
    }

    UNSTORE16_INT (in->bv_val, (*out)->tl_data_type);
    memcpy ((*out)->tl_data_contents, in->bv_val + 2, (*out)->tl_data_length);

    return 0;
}
