int nfs4_set_rw_stateid(nfs4_stateid *stateid,
		const struct nfs_open_context *ctx,
		const struct nfs_lock_context *l_ctx,
		fmode_t fmode)
{
	const struct nfs_lockowner *lockowner = NULL;

	if (l_ctx != NULL)
		lockowner = &l_ctx->lockowner;
	return nfs4_select_rw_stateid(stateid, ctx->state, fmode, lockowner);
}
