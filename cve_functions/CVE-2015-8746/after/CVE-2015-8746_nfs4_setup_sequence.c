static int nfs4_setup_sequence(const struct nfs_server *server,
			       struct nfs4_sequence_args *args,
			       struct nfs4_sequence_res *res,
			       struct rpc_task *task)
{
	return nfs40_setup_sequence(server->nfs_client->cl_slot_tbl,
				    args, res, task);
}
