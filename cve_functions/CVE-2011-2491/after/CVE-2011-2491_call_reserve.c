call_reserve(struct rpc_task *task)
{
	dprint_status(task);

	task->tk_status  = 0;
	task->tk_action  = call_reserveresult;
	xprt_reserve(task);
}
