int wc_ecc_sig_size(ecc_key* key)
{
    int sz = wc_ecc_size(key);
    if (sz <= 0)
        return sz;

    return wc_ecc_sig_size_calc(sz);
}
