nfsd4_decode_seek(struct nfsd4_compoundargs *argp, struct nfsd4_seek *seek)
{
	DECODE_HEAD;

	status = nfsd4_decode_stateid(argp, &seek->seek_stateid);
	if (status)
		return status;

	READ_BUF(8 + 4);
	p = xdr_decode_hyper(p, &seek->seek_offset);
	seek->seek_whence = be32_to_cpup(p);

	DECODE_TAIL;
}
