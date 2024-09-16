int wc_ecc_import_private_key(const byte* priv, word32 privSz, const byte* pub,
                           word32 pubSz, ecc_key* key)
{
    return wc_ecc_import_private_key_ex(priv, privSz, pub, pubSz, key,
                                                                ECC_CURVE_DEF);
}
