nfsd4_decode_lookup(struct nfsd4_compoundargs *argp, struct nfsd4_lookup *lookup)
{
	DECODE_HEAD;

	READ_BUF(4);
	lookup->lo_len = be32_to_cpup(p++);
	READ_BUF(lookup->lo_len);
	SAVEMEM(lookup->lo_name, lookup->lo_len);
	if ((status = check_filename(lookup->lo_name, lookup->lo_len)))
		return status;

	DECODE_TAIL;
}
