static int nfs4_write_done_cb(struct rpc_task *task,
			      struct nfs_pgio_header *hdr)
{
	struct inode *inode = hdr->inode;

	trace_nfs4_write(hdr, task->tk_status);
	if (nfs4_async_handle_error(task, NFS_SERVER(inode),
				    hdr->args.context->state,
				    NULL) == -EAGAIN) {
		rpc_restart_call_prepare(task);
		return -EAGAIN;
	}
	if (task->tk_status >= 0) {
		renew_lease(NFS_SERVER(inode), hdr->timestamp);
		nfs_writeback_update_inode(hdr);
	}
	return 0;
}
