void nfs4_reset_read(struct rpc_task *task, struct nfs_read_data *data)
{
	dprintk("%s Reset task for i/o through\n", __func__);
	put_lseg(data->lseg);
	data->lseg = NULL;
	/* offsets will differ in the dense stripe case */
	data->args.offset = data->mds_offset;
	data->ds_clp = NULL;
	data->args.fh     = NFS_FH(data->inode);
	data->read_done_cb = nfs4_read_done_cb;
	task->tk_ops = data->mds_ops;
	rpc_task_reset_client(task, NFS_CLIENT(data->inode));
}
