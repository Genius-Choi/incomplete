static struct rpc_task *_nfs41_free_stateid(struct nfs_server *server,
		nfs4_stateid *stateid,
		struct rpc_cred *cred,
		bool privileged)
{
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_FREE_STATEID],
		.rpc_cred = cred,
	};
	struct rpc_task_setup task_setup = {
		.rpc_client = server->client,
		.rpc_message = &msg,
		.callback_ops = &nfs41_free_stateid_ops,
		.flags = RPC_TASK_ASYNC,
	};
	struct nfs_free_stateid_data *data;

	nfs4_state_protect(server->nfs_client, NFS_SP4_MACH_CRED_STATEID,
		&task_setup.rpc_client, &msg);

	dprintk("NFS call  free_stateid %p\n", stateid);
	data = kmalloc(sizeof(*data), GFP_NOFS);
	if (!data)
		return ERR_PTR(-ENOMEM);
	data->server = server;
	nfs4_stateid_copy(&data->args.stateid, stateid);

	task_setup.callback_data = data;

	msg.rpc_argp = &data->args;
	msg.rpc_resp = &data->res;
	nfs4_init_sequence(&data->args.seq_args, &data->res.seq_res, 0);
	if (privileged)
		nfs4_set_sequence_privileged(&data->args.seq_args);

	return rpc_run_task(&task_setup);
}
