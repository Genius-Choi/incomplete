static void encode_stateid(struct xdr_stream *xdr, const struct nfs_open_context *ctx, const struct nfs_lock_context *l_ctx, int zero_seqid)
{
	nfs4_stateid stateid;
	__be32 *p;

	p = reserve_space(xdr, NFS4_STATEID_SIZE);
	if (ctx->state != NULL) {
		nfs4_copy_stateid(&stateid, ctx->state, l_ctx->lockowner, l_ctx->pid);
		if (zero_seqid)
			stateid.stateid.seqid = 0;
		xdr_encode_opaque_fixed(p, stateid.data, NFS4_STATEID_SIZE);
	} else
		xdr_encode_opaque_fixed(p, zero_stateid.data, NFS4_STATEID_SIZE);
}
