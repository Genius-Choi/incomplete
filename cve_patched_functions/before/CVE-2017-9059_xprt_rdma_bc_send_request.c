xprt_rdma_bc_send_request(struct rpc_task *task)
{
	struct rpc_rqst *rqst = task->tk_rqstp;
	struct svc_xprt *sxprt = rqst->rq_xprt->bc_xprt;
	struct svcxprt_rdma *rdma;
	int ret;

	dprintk("svcrdma: sending bc call with xid: %08x\n",
		be32_to_cpu(rqst->rq_xid));

	if (!mutex_trylock(&sxprt->xpt_mutex)) {
		rpc_sleep_on(&sxprt->xpt_bc_pending, task, NULL);
		if (!mutex_trylock(&sxprt->xpt_mutex))
			return -EAGAIN;
		rpc_wake_up_queued_task(&sxprt->xpt_bc_pending, task);
	}

	ret = -ENOTCONN;
	rdma = container_of(sxprt, struct svcxprt_rdma, sc_xprt);
	if (!test_bit(XPT_DEAD, &sxprt->xpt_flags))
		ret = rpcrdma_bc_send_request(rdma, rqst);

	mutex_unlock(&sxprt->xpt_mutex);

	if (ret < 0)
		return ret;
	return 0;
}
