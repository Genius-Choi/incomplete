int wc_ecc_sig_size_calc(int sz)
{
    return (sz * 2) + SIG_HEADER_SZ + ECC_MAX_PAD_SZ;
}
