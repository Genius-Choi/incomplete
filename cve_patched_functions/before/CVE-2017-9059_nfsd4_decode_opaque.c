static __be32 nfsd4_decode_opaque(struct nfsd4_compoundargs *argp, struct xdr_netobj *o)
{
	__be32 *p;

	READ_BUF(4);
	o->len = be32_to_cpup(p++);

	if (o->len == 0 || o->len > NFS4_OPAQUE_LIMIT)
		return nfserr_bad_xdr;

	READ_BUF(o->len);
	SAVEMEM(o->data, o->len);
	return nfs_ok;
xdr_error:
	return nfserr_bad_xdr;
}
