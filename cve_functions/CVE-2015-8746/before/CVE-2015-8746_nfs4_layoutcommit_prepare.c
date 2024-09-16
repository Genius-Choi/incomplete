static void nfs4_layoutcommit_prepare(struct rpc_task *task, void *calldata)
{
	struct nfs4_layoutcommit_data *data = calldata;
	struct nfs_server *server = NFS_SERVER(data->args.inode);
	struct nfs4_session *session = nfs4_get_session(server);

	nfs41_setup_sequence(session,
			&data->args.seq_args,
			&data->res.seq_res,
			task);
}
