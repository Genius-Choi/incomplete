nfs3svc_decode_accessargs(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd3_accessargs *args)
{
	p = decode_fh(p, &args->fh);
	if (!p)
		return 0;
	args->access = ntohl(*p++);

	return xdr_argsize_check(rqstp, p);
}
