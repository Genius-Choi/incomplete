nfsd4_decode_fallocate(struct nfsd4_compoundargs *argp,
		       struct nfsd4_fallocate *fallocate)
{
	DECODE_HEAD;

	status = nfsd4_decode_stateid(argp, &fallocate->falloc_stateid);
	if (status)
		return status;

	READ_BUF(16);
	p = xdr_decode_hyper(p, &fallocate->falloc_offset);
	xdr_decode_hyper(p, &fallocate->falloc_length);

	DECODE_TAIL;
}
