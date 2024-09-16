static void nfs4_reclaim_complete_prepare(struct rpc_task *task, void *data)
{
	struct nfs4_reclaim_complete_data *calldata = data;

	nfs41_setup_sequence(calldata->clp->cl_session,
			&calldata->arg.seq_args,
			&calldata->res.seq_res,
			task);
}
