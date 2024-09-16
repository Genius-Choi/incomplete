static int nfs4_proc_rename_done(struct rpc_task *task, struct inode *old_dir,
				 struct inode *new_dir)
{
	struct nfs_renamedata *data = task->tk_calldata;
	struct nfs_renameres *res = &data->res;

	if (!nfs4_sequence_done(task, &res->seq_res))
		return 0;
	if (nfs4_async_handle_error(task, res->server, NULL, &data->timeout) == -EAGAIN)
		return 0;

	update_changeattr(old_dir, &res->old_cinfo);
	update_changeattr(new_dir, &res->new_cinfo);
	return 1;
}
