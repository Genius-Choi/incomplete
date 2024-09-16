size_t rpc_peeraddr(struct rpc_clnt *clnt, struct sockaddr *buf, size_t bufsize)
{
	size_t bytes;
	struct rpc_xprt *xprt = clnt->cl_xprt;

	bytes = sizeof(xprt->addr);
	if (bytes > bufsize)
		bytes = bufsize;
	memcpy(buf, &clnt->cl_xprt->addr, bytes);
	return xprt->addrlen;
}
