size_t rpc_max_payload(struct rpc_clnt *clnt)
{
	return clnt->cl_xprt->max_payload;
}
