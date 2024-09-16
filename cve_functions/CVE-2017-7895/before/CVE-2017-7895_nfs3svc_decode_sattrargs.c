nfs3svc_decode_sattrargs(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd3_sattrargs *args)
{
	p = decode_fh(p, &args->fh);
	if (!p)
		return 0;
	p = decode_sattr3(p, &args->attrs);

	if ((args->check_guard = ntohl(*p++)) != 0) { 
		struct timespec time; 
		p = decode_time3(p, &time);
		args->guardtime = time.tv_sec;
	}

	return xdr_argsize_check(rqstp, p);
}
