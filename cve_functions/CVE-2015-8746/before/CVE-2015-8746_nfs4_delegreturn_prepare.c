static void nfs4_delegreturn_prepare(struct rpc_task *task, void *data)
{
	struct nfs4_delegreturndata *d_data;

	d_data = (struct nfs4_delegreturndata *)data;

	if (d_data->roc &&
	    pnfs_roc_drain(d_data->inode, &d_data->roc_barrier, task))
		return;

	nfs4_setup_sequence(d_data->res.server,
			&d_data->args.seq_args,
			&d_data->res.seq_res,
			task);
}
