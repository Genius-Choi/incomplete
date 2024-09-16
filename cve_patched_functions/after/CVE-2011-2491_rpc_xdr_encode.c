rpc_xdr_encode(struct rpc_task *task)
{
	struct rpc_rqst	*req = task->tk_rqstp;
	kxdreproc_t	encode;
	__be32		*p;

	dprint_status(task);

	rpc_xdr_buf_init(&req->rq_snd_buf,
			 req->rq_buffer,
			 req->rq_callsize);
	rpc_xdr_buf_init(&req->rq_rcv_buf,
			 (char *)req->rq_buffer + req->rq_callsize,
			 req->rq_rcvsize);

	p = rpc_encode_header(task);
	if (p == NULL) {
		printk(KERN_INFO "RPC: couldn't encode RPC header, exit EIO\n");
		rpc_exit(task, -EIO);
		return;
	}

	encode = task->tk_msg.rpc_proc->p_encode;
	if (encode == NULL)
		return;

	task->tk_status = rpcauth_wrap_req(task, encode, req, p,
			task->tk_msg.rpc_argp);
}
