static char *savemem(struct nfsd4_compoundargs *argp, __be32 *p, int nbytes)
{
	void *ret;

	ret = svcxdr_tmpalloc(argp, nbytes);
	if (!ret)
		return NULL;
	memcpy(ret, p, nbytes);
	return ret;
}
