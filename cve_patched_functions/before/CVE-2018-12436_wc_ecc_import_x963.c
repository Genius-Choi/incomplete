int wc_ecc_import_x963(const byte* in, word32 inLen, ecc_key* key)
{
    return wc_ecc_import_x963_ex(in, inLen, key, ECC_CURVE_DEF);
}
