static int nfs4_read_done_cb(struct rpc_task *task, struct nfs_pgio_header *hdr)
{
	struct nfs_server *server = NFS_SERVER(hdr->inode);

	trace_nfs4_read(hdr, task->tk_status);
	if (nfs4_async_handle_error(task, server,
				    hdr->args.context->state,
				    NULL) == -EAGAIN) {
		rpc_restart_call_prepare(task);
		return -EAGAIN;
	}

	__nfs4_read_done_cb(hdr);
	if (task->tk_status > 0)
		renew_lease(server, hdr->timestamp);
	return 0;
}
