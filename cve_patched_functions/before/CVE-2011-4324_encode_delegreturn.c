static int encode_delegreturn(struct xdr_stream *xdr, const nfs4_stateid *stateid)
{
	__be32 *p;

	RESERVE_SPACE(4+NFS4_STATEID_SIZE);

	WRITE32(OP_DELEGRETURN);
	WRITEMEM(stateid->data, NFS4_STATEID_SIZE);
	return 0;

}
