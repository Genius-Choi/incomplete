void rpc_force_rebind(struct rpc_clnt *clnt)
{
	if (clnt->cl_autobind)
		xprt_clear_bound(clnt->cl_xprt);
}
