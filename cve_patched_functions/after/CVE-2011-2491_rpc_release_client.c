rpc_release_client(struct rpc_clnt *clnt)
{
	dprintk("RPC:       rpc_release_client(%p)\n", clnt);

	if (list_empty(&clnt->cl_tasks))
		wake_up(&destroy_wait);
	if (atomic_dec_and_test(&clnt->cl_count))
		rpc_free_auth(clnt);
}
