ar6000_cookie_init(struct ar6_softc *ar)
{
    u32 i;

    ar->arCookieList = NULL;
    ar->arCookieCount = 0;

    A_MEMZERO(s_ar_cookie_mem, sizeof(s_ar_cookie_mem));

    for (i = 0; i < MAX_COOKIE_NUM; i++) {
        ar6000_free_cookie(ar, &s_ar_cookie_mem[i]);
    }
}
