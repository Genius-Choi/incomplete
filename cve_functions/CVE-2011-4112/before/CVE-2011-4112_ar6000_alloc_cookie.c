ar6000_alloc_cookie(struct ar6_softc  *ar)
{
    struct ar_cookie   *cookie;

    cookie = ar->arCookieList;
    if(cookie != NULL)
    {
        ar->arCookieList = cookie->arc_list_next;
        ar->arCookieCount--;
    }

    return cookie;
}
