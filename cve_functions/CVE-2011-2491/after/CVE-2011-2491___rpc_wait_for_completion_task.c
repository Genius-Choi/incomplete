int __rpc_wait_for_completion_task(struct rpc_task *task, int (*action)(void *))
{
	if (action == NULL)
		action = rpc_wait_bit_killable;
	return out_of_line_wait_on_bit(&task->tk_runstate, RPC_TASK_ACTIVE,
			action, TASK_KILLABLE);
}
