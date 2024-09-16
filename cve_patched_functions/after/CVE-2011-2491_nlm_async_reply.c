int nlm_async_reply(struct nlm_rqst *req, u32 proc, const struct rpc_call_ops *tk_ops)
{
	struct rpc_message msg = {
		.rpc_argp	= &req->a_res,
	};
	return nlm_do_async_call(req, proc, &msg, tk_ops);
}
