tl_data2berval (krb5_tl_data *in, struct berval **out)
{
    *out = (struct berval *) malloc (sizeof (struct berval));
    if (*out == NULL)
        return ENOMEM;

    (*out)->bv_len = in->tl_data_length + 2;
    (*out)->bv_val =  (char *) malloc ((*out)->bv_len);
    if ((*out)->bv_val == NULL) {
        free (*out);
        return ENOMEM;
    }

    STORE16_INT((*out)->bv_val, in->tl_data_type);
    memcpy ((*out)->bv_val + 2, in->tl_data_contents, in->tl_data_length);

    return 0;
}
