nfsd4_decode_commit(struct nfsd4_compoundargs *argp, struct nfsd4_commit *commit)
{
	DECODE_HEAD;

	READ_BUF(12);
	p = xdr_decode_hyper(p, &commit->co_offset);
	commit->co_count = be32_to_cpup(p++);

	DECODE_TAIL;
}
