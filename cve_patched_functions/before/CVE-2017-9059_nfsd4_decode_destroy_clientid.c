static __be32 nfsd4_decode_destroy_clientid(struct nfsd4_compoundargs *argp, struct nfsd4_destroy_clientid *dc)
{
	DECODE_HEAD;

	READ_BUF(8);
	COPYMEM(&dc->clientid, 8);

	DECODE_TAIL;
}
