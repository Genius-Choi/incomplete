const char* wc_ecc_get_name(int curve_id)
{
    int curve_idx = wc_ecc_get_curve_idx(curve_id);
    if (curve_idx == ECC_CURVE_INVALID)
        return NULL;
    return ecc_sets[curve_idx].name;
}
