newSiteconfRec(void)
{
    struct siteconf_rec *ent;

    ent = New(struct siteconf_rec);
    ent->next = NULL;
    ent->url = NULL;
    ent->re_url = NULL;
    ent->url_exact = FALSE;
    memset(ent->mask, 0, sizeof(ent->mask));

    ent->substitute_url = NULL;
#ifdef USE_M17N
    ent->url_charset = 0;
#endif
    return ent;
}
