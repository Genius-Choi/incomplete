void rpc_task_reset_client(struct rpc_task *task, struct rpc_clnt *clnt)
{
	rpc_task_release_client(task);
	rpc_task_set_client(task, clnt);
}
