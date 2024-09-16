nfsd4_decode_locku(struct nfsd4_compoundargs *argp, struct nfsd4_locku *locku)
{
	DECODE_HEAD;

	READ_BUF(8);
	locku->lu_type = be32_to_cpup(p++);
	if ((locku->lu_type < NFS4_READ_LT) || (locku->lu_type > NFS4_WRITEW_LT))
		goto xdr_error;
	locku->lu_seqid = be32_to_cpup(p++);
	status = nfsd4_decode_stateid(argp, &locku->lu_stateid);
	if (status)
		return status;
	READ_BUF(16);
	p = xdr_decode_hyper(p, &locku->lu_offset);
	p = xdr_decode_hyper(p, &locku->lu_length);

	DECODE_TAIL;
}
