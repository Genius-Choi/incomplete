static int _nfs4_free_stateid(struct nfs_server *server, struct nfs4_state *state)
{
	int status;
	struct nfs41_free_stateid_args args = {
		.stateid = &state->stateid,
	};
	struct nfs41_free_stateid_res res;
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_FREE_STATEID],
		.rpc_argp = &args,
		.rpc_resp = &res,
	};

	args.seq_args.sa_session = res.seq_res.sr_session = NULL;
	status = nfs4_call_sync_sequence(server->client, server, &msg, &args.seq_args, &res.seq_res, 0, 1);
	return status;
}
