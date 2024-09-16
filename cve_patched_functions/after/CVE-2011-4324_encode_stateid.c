static void encode_stateid(struct xdr_stream *xdr, const struct nfs_open_context *ctx)
{
	nfs4_stateid stateid;
	__be32 *p;

	RESERVE_SPACE(NFS4_STATEID_SIZE);
	if (ctx->state != NULL) {
		nfs4_copy_stateid(&stateid, ctx->state, ctx->lockowner);
		WRITEMEM(stateid.data, NFS4_STATEID_SIZE);
	} else
		WRITEMEM(zero_stateid.data, NFS4_STATEID_SIZE);
}
