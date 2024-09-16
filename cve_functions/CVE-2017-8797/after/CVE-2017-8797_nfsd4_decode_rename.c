nfsd4_decode_rename(struct nfsd4_compoundargs *argp, struct nfsd4_rename *rename)
{
	DECODE_HEAD;

	READ_BUF(4);
	rename->rn_snamelen = be32_to_cpup(p++);
	READ_BUF(rename->rn_snamelen);
	SAVEMEM(rename->rn_sname, rename->rn_snamelen);
	READ_BUF(4);
	rename->rn_tnamelen = be32_to_cpup(p++);
	READ_BUF(rename->rn_tnamelen);
	SAVEMEM(rename->rn_tname, rename->rn_tnamelen);
	if ((status = check_filename(rename->rn_sname, rename->rn_snamelen)))
		return status;
	if ((status = check_filename(rename->rn_tname, rename->rn_tnamelen)))
		return status;

	DECODE_TAIL;
}
