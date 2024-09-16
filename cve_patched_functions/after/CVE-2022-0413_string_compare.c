string_compare(const void *s1, const void *s2)
{
    if (sort_lc)
	return strcoll((char *)s1, (char *)s2);
    return sort_ic ? STRICMP(s1, s2) : STRCMP(s1, s2);
}
