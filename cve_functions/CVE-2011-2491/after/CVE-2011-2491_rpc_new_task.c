struct rpc_task *rpc_new_task(const struct rpc_task_setup *setup_data)
{
	struct rpc_task	*task = setup_data->task;
	unsigned short flags = 0;

	if (task == NULL) {
		task = rpc_alloc_task();
		if (task == NULL) {
			rpc_release_calldata(setup_data->callback_ops,
					setup_data->callback_data);
			return ERR_PTR(-ENOMEM);
		}
		flags = RPC_TASK_DYNAMIC;
	}

	rpc_init_task(task, setup_data);
	task->tk_flags |= flags;
	dprintk("RPC:       allocated task %p\n", task);
	return task;
}
