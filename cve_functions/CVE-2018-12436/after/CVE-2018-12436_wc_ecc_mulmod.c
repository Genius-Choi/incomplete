int wc_ecc_mulmod(mp_int* k, ecc_point *G, ecc_point *R, mp_int* a,
                  mp_int* modulus, int map)
{
    return wc_ecc_mulmod_ex(k, G, R, a, modulus, map, NULL);
}
