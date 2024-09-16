http_DoConnection(const struct http *hp)
{
	char *p, *q;
	const char *ret;
	unsigned u;

	if (!http_GetHdr(hp, H_Connection, &p)) {
		if (hp->protover < 11)
			return ("not HTTP/1.1");
		return (NULL);
	}
	ret = NULL;
	AN(p);
	for (; *p; p++) {
		if (vct_issp(*p))
			continue;
		if (*p == ',')
			continue;
		for (q = p + 1; *q; q++)
			if (*q == ',' || vct_issp(*q))
				break;
		u = pdiff(p, q);
		if (u == 5 && !strncasecmp(p, "close", u))
			ret = "Connection: close";
		u = http_findhdr(hp, u, p);
		if (u != 0)
			hp->hdf[u] |= HDF_FILTER;
		if (!*q)
			break;
		p = q;
	}
	return (ret);
}
