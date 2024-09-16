static __be32 nfsd4_decode_reclaim_complete(struct nfsd4_compoundargs *argp, struct nfsd4_reclaim_complete *rc)
{
	DECODE_HEAD;

	READ_BUF(4);
	rc->rca_one_fs = be32_to_cpup(p++);

	DECODE_TAIL;
}
