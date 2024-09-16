int wc_ecc_import_unsigned(ecc_key* key, byte* qx, byte* qy,
                   byte* d, int curve_id)
{
    return wc_ecc_import_raw_private(key, (const char*)qx, (const char*)qy,
        (const char*)d, curve_id, ECC_TYPE_UNSIGNED_BIN);
}
