static int nfs41_free_stateid(struct nfs_server *server,
		nfs4_stateid *stateid,
		struct rpc_cred *cred)
{
	struct rpc_task *task;
	int ret;

	task = _nfs41_free_stateid(server, stateid, cred, true);
	if (IS_ERR(task))
		return PTR_ERR(task);
	ret = rpc_wait_for_completion_task(task);
	if (!ret)
		ret = task->tk_status;
	rpc_put_task(task);
	return ret;
}
