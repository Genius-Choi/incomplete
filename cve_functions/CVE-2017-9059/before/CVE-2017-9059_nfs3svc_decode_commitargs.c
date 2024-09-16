nfs3svc_decode_commitargs(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd3_commitargs *args)
{
	p = decode_fh(p, &args->fh);
	if (!p)
		return 0;
	p = xdr_decode_hyper(p, &args->offset);
	args->count = ntohl(*p++);

	return xdr_argsize_check(rqstp, p);
}
