int wc_ecc_curve_cache_init(void)
{
    int ret = 0;
#if defined(ECC_CACHE_CURVE) && !defined(SINGLE_THREADED)
    ret = wc_InitMutex(&ecc_curve_cache_mutex);
#endif
    return ret;
}
