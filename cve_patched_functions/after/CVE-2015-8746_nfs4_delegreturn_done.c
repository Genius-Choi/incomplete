static void nfs4_delegreturn_done(struct rpc_task *task, void *calldata)
{
	struct nfs4_delegreturndata *data = calldata;

	if (!nfs4_sequence_done(task, &data->res.seq_res))
		return;

	trace_nfs4_delegreturn_exit(&data->args, &data->res, task->tk_status);
	switch (task->tk_status) {
	case 0:
		renew_lease(data->res.server, data->timestamp);
	case -NFS4ERR_ADMIN_REVOKED:
	case -NFS4ERR_DELEG_REVOKED:
	case -NFS4ERR_BAD_STATEID:
	case -NFS4ERR_OLD_STATEID:
	case -NFS4ERR_STALE_STATEID:
	case -NFS4ERR_EXPIRED:
		task->tk_status = 0;
		if (data->roc)
			pnfs_roc_set_barrier(data->inode, data->roc_barrier);
		break;
	default:
		if (nfs4_async_handle_error(task, data->res.server,
					    NULL, NULL) == -EAGAIN) {
			rpc_restart_call_prepare(task);
			return;
		}
	}
	data->rpc_status = task->tk_status;
}
