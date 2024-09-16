int wc_ecc_export_public_raw(ecc_key* key, byte* qx, word32* qxLen,
                             byte* qy, word32* qyLen)
{
    return wc_ecc_export_raw(key, qx, qxLen, qy, qyLen, NULL, NULL);
}
