nfsd4_decode_putfh(struct nfsd4_compoundargs *argp, struct nfsd4_putfh *putfh)
{
	DECODE_HEAD;

	READ_BUF(4);
	putfh->pf_fhlen = be32_to_cpup(p++);
	if (putfh->pf_fhlen > NFS4_FHSIZE)
		goto xdr_error;
	READ_BUF(putfh->pf_fhlen);
	SAVEMEM(putfh->pf_fhval, putfh->pf_fhlen);

	DECODE_TAIL;
}
