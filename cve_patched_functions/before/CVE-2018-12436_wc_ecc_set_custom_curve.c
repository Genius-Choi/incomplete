int wc_ecc_set_custom_curve(ecc_key* key, const ecc_set_type* dp)
{
    if (key == NULL || dp == NULL) {
        return BAD_FUNC_ARG;
    }

    key->idx = ECC_CUSTOM_IDX;
    key->dp = dp;

    return 0;
}
