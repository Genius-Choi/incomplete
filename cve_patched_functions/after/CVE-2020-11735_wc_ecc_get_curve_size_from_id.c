int wc_ecc_get_curve_size_from_id(int curve_id)
{
    int curve_idx = wc_ecc_get_curve_idx(curve_id);
    if (curve_idx == ECC_CURVE_INVALID)
        return ECC_BAD_ARG_E;
    return ecc_sets[curve_idx].size;
}
