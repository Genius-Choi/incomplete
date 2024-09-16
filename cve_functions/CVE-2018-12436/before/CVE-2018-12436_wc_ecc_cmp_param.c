static int wc_ecc_cmp_param(const char* curveParam,
                            const byte* param, word32 paramSz)
{
    int err = MP_OKAY;
    mp_int a, b;

    if (param == NULL || curveParam == NULL)
        return BAD_FUNC_ARG;

    if ((err = mp_init_multi(&a, &b, NULL, NULL, NULL, NULL)) != MP_OKAY)
        return err;

    if (err == MP_OKAY)
        err = mp_read_unsigned_bin(&a, param, paramSz);

    if (err == MP_OKAY)
        err = mp_read_radix(&b, curveParam, MP_RADIX_HEX);

    if (err == MP_OKAY) {
        if (mp_cmp(&a, &b) != MP_EQ) {
            err = -1;
        } else {
            err = MP_EQ;
        }
    }

    mp_clear(&a);
    mp_clear(&b);

    return err;
}
