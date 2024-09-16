void svc_rdma_cleanup(void)
{
	dprintk("SVCRDMA Module Removed, deregister RPC RDMA transport\n");
	destroy_workqueue(svc_rdma_wq);
	if (svcrdma_table_header) {
		unregister_sysctl_table(svcrdma_table_header);
		svcrdma_table_header = NULL;
	}
#if defined(CONFIG_SUNRPC_BACKCHANNEL)
	svc_unreg_xprt_class(&svc_rdma_bc_class);
#endif
	svc_unreg_xprt_class(&svc_rdma_class);
}
