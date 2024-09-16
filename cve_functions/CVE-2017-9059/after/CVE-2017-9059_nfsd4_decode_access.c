nfsd4_decode_access(struct nfsd4_compoundargs *argp, struct nfsd4_access *access)
{
	DECODE_HEAD;

	READ_BUF(4);
	access->ac_req_access = be32_to_cpup(p++);

	DECODE_TAIL;
}
