nfsd4_decode_clone(struct nfsd4_compoundargs *argp, struct nfsd4_clone *clone)
{
	DECODE_HEAD;

	status = nfsd4_decode_stateid(argp, &clone->cl_src_stateid);
	if (status)
		return status;
	status = nfsd4_decode_stateid(argp, &clone->cl_dst_stateid);
	if (status)
		return status;

	READ_BUF(8 + 8 + 8);
	p = xdr_decode_hyper(p, &clone->cl_src_pos);
	p = xdr_decode_hyper(p, &clone->cl_dst_pos);
	p = xdr_decode_hyper(p, &clone->cl_count);
	DECODE_TAIL;
}
