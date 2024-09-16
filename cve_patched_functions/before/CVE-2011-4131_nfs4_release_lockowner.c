void nfs4_release_lockowner(const struct nfs4_lock_state *lsp)
{
	struct nfs_server *server = lsp->ls_state->owner->so_server;
	struct nfs_release_lockowner_args *args;
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_RELEASE_LOCKOWNER],
	};

	if (server->nfs_client->cl_mvops->minor_version != 0)
		return;
	args = kmalloc(sizeof(*args), GFP_NOFS);
	if (!args)
		return;
	args->lock_owner.clientid = server->nfs_client->cl_clientid;
	args->lock_owner.id = lsp->ls_id.id;
	args->lock_owner.s_dev = server->s_dev;
	msg.rpc_argp = args;
	rpc_call_async(server->client, &msg, 0, &nfs4_release_lockowner_ops, args);
}
