int wc_ecc_import_raw_ex(ecc_key* key, const char* qx, const char* qy,
                   const char* d, int curve_id)
{
    return wc_ecc_import_raw_private(key, qx, qy, d, curve_id,
        ECC_TYPE_HEX_STR);

}
