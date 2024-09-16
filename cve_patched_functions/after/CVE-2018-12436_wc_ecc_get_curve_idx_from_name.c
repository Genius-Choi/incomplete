int wc_ecc_get_curve_idx_from_name(const char* curveName)
{
    int curve_idx;
    word32 len;

    if (curveName == NULL)
        return BAD_FUNC_ARG;

    len = (word32)XSTRLEN(curveName);

    for (curve_idx = 0; ecc_sets[curve_idx].size != 0; curve_idx++) {
        if (ecc_sets[curve_idx].name &&
                XSTRNCASECMP(ecc_sets[curve_idx].name, curveName, len) == 0) {
            break;
        }
    }
    if (ecc_sets[curve_idx].size == 0) {
        WOLFSSL_MSG("ecc_set curve name not found");
        return ECC_CURVE_INVALID;
    }
    return curve_idx;
}
