void nfs4_destroy_session(struct nfs4_session *session)
{
	nfs4_proc_destroy_session(session);
	dprintk("%s Destroy backchannel for xprt %p\n",
		__func__, session->clp->cl_rpcclient->cl_xprt);
	xprt_destroy_backchannel(session->clp->cl_rpcclient->cl_xprt,
				NFS41_BC_MIN_CALLBACKS);
	nfs4_destroy_slot_tables(session);
	kfree(session);
}
