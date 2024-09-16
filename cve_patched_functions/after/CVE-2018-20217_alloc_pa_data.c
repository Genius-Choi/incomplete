alloc_pa_data(krb5_preauthtype pa_type, size_t len, krb5_pa_data **out)
{
    krb5_pa_data *pa;
    uint8_t *buf = NULL;

    *out = NULL;
    if (len > 0) {
        buf = malloc(len);
        if (buf == NULL)
            return ENOMEM;
    }
    pa = malloc(sizeof(*pa));
    if (pa == NULL) {
        free(buf);
        return ENOMEM;
    }
    pa->magic = KV5M_PA_DATA;
    pa->pa_type = pa_type;
    pa->length = len;
    pa->contents = buf;
    *out = pa;
    return 0;
}
