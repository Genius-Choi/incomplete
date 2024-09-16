static void nfs41_free_stateid_prepare(struct rpc_task *task, void *calldata)
{
	struct nfs_free_stateid_data *data = calldata;
	nfs41_setup_sequence(nfs4_get_session(data->server),
			&data->args.seq_args,
			&data->res.seq_res,
			task);
}
