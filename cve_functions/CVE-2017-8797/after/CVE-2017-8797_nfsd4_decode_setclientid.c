nfsd4_decode_setclientid(struct nfsd4_compoundargs *argp, struct nfsd4_setclientid *setclientid)
{
	DECODE_HEAD;

	if (argp->minorversion >= 1)
		return nfserr_notsupp;

	READ_BUF(NFS4_VERIFIER_SIZE);
	COPYMEM(setclientid->se_verf.data, NFS4_VERIFIER_SIZE);

	status = nfsd4_decode_opaque(argp, &setclientid->se_name);
	if (status)
		return nfserr_bad_xdr;
	READ_BUF(8);
	setclientid->se_callback_prog = be32_to_cpup(p++);
	setclientid->se_callback_netid_len = be32_to_cpup(p++);
	READ_BUF(setclientid->se_callback_netid_len);
	SAVEMEM(setclientid->se_callback_netid_val, setclientid->se_callback_netid_len);
	READ_BUF(4);
	setclientid->se_callback_addr_len = be32_to_cpup(p++);

	READ_BUF(setclientid->se_callback_addr_len);
	SAVEMEM(setclientid->se_callback_addr_val, setclientid->se_callback_addr_len);
	READ_BUF(4);
	setclientid->se_callback_ident = be32_to_cpup(p++);

	DECODE_TAIL;
}
