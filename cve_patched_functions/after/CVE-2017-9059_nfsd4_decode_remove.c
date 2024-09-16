nfsd4_decode_remove(struct nfsd4_compoundargs *argp, struct nfsd4_remove *remove)
{
	DECODE_HEAD;

	READ_BUF(4);
	remove->rm_namelen = be32_to_cpup(p++);
	READ_BUF(remove->rm_namelen);
	SAVEMEM(remove->rm_name, remove->rm_namelen);
	if ((status = check_filename(remove->rm_name, remove->rm_namelen)))
		return status;

	DECODE_TAIL;
}
