getstringtime(krb5_timestamp epochtime)
{
    struct tm           tme;
    char                *strtime=NULL;
    time_t              posixtime = epochtime;

    strtime = calloc (50, 1);
    if (strtime == NULL)
        return NULL;

    if (gmtime_r(&posixtime, &tme) == NULL)
        return NULL;

    strftime(strtime, 50, "%Y%m%d%H%M%SZ", &tme);
    return strtime;
}
