nfsd4_decode_read(struct nfsd4_compoundargs *argp, struct nfsd4_read *read)
{
	DECODE_HEAD;

	status = nfsd4_decode_stateid(argp, &read->rd_stateid);
	if (status)
		return status;
	READ_BUF(12);
	p = xdr_decode_hyper(p, &read->rd_offset);
	read->rd_length = be32_to_cpup(p++);

	DECODE_TAIL;
}
