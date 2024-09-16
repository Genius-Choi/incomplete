nfs41_free_lock_state(struct nfs_server *server, struct nfs4_lock_state *lsp)
{
	struct rpc_task *task;
	struct rpc_cred *cred = lsp->ls_state->owner->so_cred;

	task = _nfs41_free_stateid(server, &lsp->ls_stateid, cred, false);
	nfs4_free_lock_state(server, lsp);
	if (IS_ERR(task))
		return;
	rpc_put_task(task);
}
