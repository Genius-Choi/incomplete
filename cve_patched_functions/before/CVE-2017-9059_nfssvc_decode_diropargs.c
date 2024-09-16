nfssvc_decode_diropargs(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd_diropargs *args)
{
	if (!(p = decode_fh(p, &args->fh))
	 || !(p = decode_filename(p, &args->name, &args->len)))
		return 0;

	return xdr_argsize_check(rqstp, p);
}
