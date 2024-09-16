int wc_ecc_size(ecc_key* key)
{
    if (key == NULL) return 0;

    return key->dp->size;
}
