static void rpc_register_client(struct rpc_clnt *clnt)
{
	spin_lock(&rpc_client_lock);
	list_add(&clnt->cl_clients, &all_clients);
	spin_unlock(&rpc_client_lock);
}
