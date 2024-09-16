static void compat_dh_get0_key(const DH *dh, const BIGNUM **pub,
                               const BIGNUM **priv)
{
    if (pub != NULL)
        *pub = dh->pub_key;
    if (priv != NULL)
        *priv = dh->priv_key;
}
