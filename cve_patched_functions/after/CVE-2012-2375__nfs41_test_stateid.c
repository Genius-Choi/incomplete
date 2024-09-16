static int _nfs41_test_stateid(struct nfs_server *server, nfs4_stateid *stateid)
{
	int status;
	struct nfs41_test_stateid_args args = {
		.stateid = stateid,
	};
	struct nfs41_test_stateid_res res;
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_TEST_STATEID],
		.rpc_argp = &args,
		.rpc_resp = &res,
	};

	nfs41_init_sequence(&args.seq_args, &res.seq_res, 0);
	status = nfs4_call_sync_sequence(server->client, server, &msg, &args.seq_args, &res.seq_res, 1);

	if (status == NFS_OK)
		return res.status;
	return status;
}
