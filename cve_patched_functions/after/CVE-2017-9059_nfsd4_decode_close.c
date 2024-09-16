nfsd4_decode_close(struct nfsd4_compoundargs *argp, struct nfsd4_close *close)
{
	DECODE_HEAD;

	READ_BUF(4);
	close->cl_seqid = be32_to_cpup(p++);
	return nfsd4_decode_stateid(argp, &close->cl_stateid);

	DECODE_TAIL;
}
