static void nfs4_layoutreturn_done(struct rpc_task *task, void *calldata)
{
	struct nfs4_layoutreturn *lrp = calldata;
	struct nfs_server *server;

	dprintk("--> %s\n", __func__);

	if (!nfs41_sequence_done(task, &lrp->res.seq_res))
		return;

	server = NFS_SERVER(lrp->args.inode);
	switch (task->tk_status) {
	default:
		task->tk_status = 0;
	case 0:
		break;
	case -NFS4ERR_DELAY:
		if (nfs4_async_handle_error(task, server, NULL, NULL) != -EAGAIN)
			break;
		rpc_restart_call_prepare(task);
		return;
	}
	dprintk("<-- %s\n", __func__);
}
