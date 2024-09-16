static void _wc_ecc_curve_free(ecc_curve_spec* curve)
{
    if (curve == NULL) {
        return;
    }

    if (curve->load_mask & ECC_CURVE_FIELD_PRIME)
        mp_clear(curve->prime);
    if (curve->load_mask & ECC_CURVE_FIELD_AF)
        mp_clear(curve->Af);
#ifdef USE_ECC_B_PARAM
    if (curve->load_mask & ECC_CURVE_FIELD_BF)
        mp_clear(curve->Bf);
#endif
    if (curve->load_mask & ECC_CURVE_FIELD_ORDER)
        mp_clear(curve->order);
    if (curve->load_mask & ECC_CURVE_FIELD_GX)
        mp_clear(curve->Gx);
    if (curve->load_mask & ECC_CURVE_FIELD_GY)
        mp_clear(curve->Gy);

    curve->load_mask = 0;
}
