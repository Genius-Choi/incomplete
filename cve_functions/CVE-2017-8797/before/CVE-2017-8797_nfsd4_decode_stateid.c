nfsd4_decode_stateid(struct nfsd4_compoundargs *argp, stateid_t *sid)
{
	DECODE_HEAD;

	READ_BUF(sizeof(stateid_t));
	sid->si_generation = be32_to_cpup(p++);
	COPYMEM(&sid->si_opaque, sizeof(stateid_opaque_t));

	DECODE_TAIL;
}
