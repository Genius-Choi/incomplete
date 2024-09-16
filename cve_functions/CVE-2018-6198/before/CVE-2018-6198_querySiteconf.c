querySiteconf(const ParsedURL *query_pu, int field)
{
    const struct siteconf_rec *ent;
    Str u;
    char *firstp, *lastp;

    if (field < 0 || field >= SCONF_N_FIELD)
	return NULL;
    if (!query_pu || IS_EMPTY_PARSED_URL(query_pu))
	return NULL;
    u = parsedURL2Str((ParsedURL *)query_pu);
    if (u->length == 0)
	return NULL;

    for (ent = siteconf_head; ent; ent = ent->next) {
	if (!SCONF_TEST(ent, field))
	    continue;
	if (ent->re_url) {
	    if (RegexMatch(ent->re_url, u->ptr, u->length, 1)) {
		MatchedPosition(ent->re_url, &firstp, &lastp);
		if (!ent->url_exact)
		    goto url_found;
		if (firstp != u->ptr || lastp == firstp)
		    continue;
		if (*lastp == 0 || *lastp == '?' || *(lastp - 1) == '?' ||
		    *lastp == '#' || *(lastp - 1) == '#')
		    goto url_found;
	    }
	} else {
	    int matchlen = strmatchlen(ent->url, u->ptr, u->length);
	    if (matchlen == 0 || ent->url[matchlen] != 0)
		continue;
	    firstp = u->ptr;
	    lastp = u->ptr + matchlen;
	    if (*lastp == 0 || *lastp == '?' || *(lastp - 1) == '?' ||
		*lastp == '#' || *(lastp - 1) == '#')
		goto url_found;
	    if (!ent->url_exact && (*lastp == '/' || *(lastp - 1) == '/'))
		goto url_found;
	}
    }
    return NULL;

url_found:
    switch (field) {
    case SCONF_SUBSTITUTE_URL:
	if (ent->substitute_url && *ent->substitute_url) {
	    Str tmp = Strnew_charp_n(u->ptr, firstp - u->ptr);
	    Strcat_charp(tmp, ent->substitute_url);
	    Strcat_charp(tmp, lastp);
	    return tmp->ptr;
	}
	return NULL;
#ifdef USE_M17N
    case SCONF_URL_CHARSET:
	return &ent->url_charset;
#endif
    case SCONF_NO_REFERER_FROM:
	return &ent->no_referer_from;
    case SCONF_NO_REFERER_TO:
	return &ent->no_referer_to;
    }
    return NULL;
}
