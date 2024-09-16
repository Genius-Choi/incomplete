nfsd4_decode_secinfo_no_name(struct nfsd4_compoundargs *argp,
		     struct nfsd4_secinfo_no_name *sin)
{
	DECODE_HEAD;

	READ_BUF(4);
	sin->sin_style = be32_to_cpup(p++);
	DECODE_TAIL;
}
