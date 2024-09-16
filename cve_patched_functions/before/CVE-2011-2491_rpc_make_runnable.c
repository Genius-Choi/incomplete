static void rpc_make_runnable(struct rpc_task *task)
{
	rpc_clear_queued(task);
	if (rpc_test_and_set_running(task))
		return;
	if (RPC_IS_ASYNC(task)) {
		INIT_WORK(&task->u.tk_work, rpc_async_schedule);
		queue_work(rpciod_workqueue, &task->u.tk_work);
	} else
		wake_up_bit(&task->tk_runstate, RPC_TASK_QUEUED);
}
