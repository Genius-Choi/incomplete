static void rpc_show_task(const struct rpc_clnt *clnt,
			  const struct rpc_task *task)
{
	const char *rpc_waitq = "none";

	if (RPC_IS_QUEUED(task))
		rpc_waitq = rpc_qname(task->tk_waitqueue);

	printk(KERN_INFO "%5u %04x %6d %8p %8p %8ld %8p %sv%u %s a:%ps q:%s\n",
		task->tk_pid, task->tk_flags, task->tk_status,
		clnt, task->tk_rqstp, task->tk_timeout, task->tk_ops,
		clnt->cl_protname, clnt->cl_vers, rpc_proc_name(task),
		task->tk_action, rpc_waitq);
}
