static int nfs_callback_start_svc(int minorversion, struct rpc_xprt *xprt,
				  struct svc_serv *serv)
{
	int nrservs = nfs_callback_nr_threads;
	int ret;

	nfs_callback_bc_serv(minorversion, xprt, serv);

	if (nrservs < NFS4_MIN_NR_CALLBACK_THREADS)
		nrservs = NFS4_MIN_NR_CALLBACK_THREADS;

	if (serv->sv_nrthreads-1 == nrservs)
		return 0;

	ret = serv->sv_ops->svo_setup(serv, NULL, nrservs);
	if (ret) {
		serv->sv_ops->svo_setup(serv, NULL, 0);
		return ret;
	}
	dprintk("nfs_callback_up: service started\n");
	return 0;
}
