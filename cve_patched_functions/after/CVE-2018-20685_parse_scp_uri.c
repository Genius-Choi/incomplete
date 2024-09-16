parse_scp_uri(const char *uri, char **userp, char **hostp, int *portp,
     char **pathp)
{
	int r;

	r = parse_uri("scp", uri, userp, hostp, portp, pathp);
	if (r == 0 && *pathp == NULL)
		*pathp = xstrdup(".");
	return r;
}
