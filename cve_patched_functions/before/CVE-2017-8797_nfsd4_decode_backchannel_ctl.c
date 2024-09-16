static __be32 nfsd4_decode_backchannel_ctl(struct nfsd4_compoundargs *argp, struct nfsd4_backchannel_ctl *bc)
{
	DECODE_HEAD;

	READ_BUF(4);
	bc->bc_cb_program = be32_to_cpup(p++);
	nfsd4_decode_cb_sec(argp, &bc->bc_cb_sec);

	DECODE_TAIL;
}
