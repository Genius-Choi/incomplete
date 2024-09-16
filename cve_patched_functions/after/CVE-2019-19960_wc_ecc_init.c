int wc_ecc_init(ecc_key* key)
{
    return wc_ecc_init_ex(key, NULL, INVALID_DEVID);
}
