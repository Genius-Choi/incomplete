static int nlm_do_async_call(struct nlm_rqst *req, u32 proc, struct rpc_message *msg, const struct rpc_call_ops *tk_ops)
{
	struct rpc_task *task;

	task = __nlm_async_call(req, proc, msg, tk_ops);
	if (IS_ERR(task))
		return PTR_ERR(task);
	rpc_put_task(task);
	return 0;
}
