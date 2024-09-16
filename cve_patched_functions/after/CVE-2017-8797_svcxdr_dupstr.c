svcxdr_dupstr(struct nfsd4_compoundargs *argp, void *buf, u32 len)
{
	char *p = svcxdr_tmpalloc(argp, len + 1);

	if (!p)
		return NULL;
	memcpy(p, buf, len);
	p[len] = '\0';
	return p;
}
