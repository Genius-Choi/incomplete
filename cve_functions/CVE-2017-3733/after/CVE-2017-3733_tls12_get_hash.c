const EVP_MD *tls12_get_hash(unsigned char hash_alg)
{
    const tls12_hash_info *inf;
    if (hash_alg == TLSEXT_hash_md5 && FIPS_mode())
        return NULL;
    inf = tls12_get_hash_info(hash_alg);
    if (!inf)
        return NULL;
    return ssl_md(inf->md_idx);
}
