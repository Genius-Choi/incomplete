xprt_rdma_bc_put(struct rpc_xprt *xprt)
{
	dprintk("svcrdma: %s: xprt %p\n", __func__, xprt);

	xprt_free(xprt);
	module_put(THIS_MODULE);
}
