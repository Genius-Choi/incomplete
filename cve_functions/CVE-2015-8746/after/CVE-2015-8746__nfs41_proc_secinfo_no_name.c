_nfs41_proc_secinfo_no_name(struct nfs_server *server, struct nfs_fh *fhandle,
		    struct nfs_fsinfo *info,
		    struct nfs4_secinfo_flavors *flavors, bool use_integrity)
{
	struct nfs41_secinfo_no_name_args args = {
		.style = SECINFO_STYLE_CURRENT_FH,
	};
	struct nfs4_secinfo_res res = {
		.flavors = flavors,
	};
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_SECINFO_NO_NAME],
		.rpc_argp = &args,
		.rpc_resp = &res,
	};
	struct rpc_clnt *clnt = server->client;
	struct rpc_cred *cred = NULL;
	int status;

	if (use_integrity) {
		clnt = server->nfs_client->cl_rpcclient;
		cred = nfs4_get_clid_cred(server->nfs_client);
		msg.rpc_cred = cred;
	}

	dprintk("--> %s\n", __func__);
	status = nfs4_call_sync(clnt, server, &msg, &args.seq_args,
				&res.seq_res, 0);
	dprintk("<-- %s status=%d\n", __func__, status);

	if (cred)
		put_rpccred(cred);

	return status;
}
