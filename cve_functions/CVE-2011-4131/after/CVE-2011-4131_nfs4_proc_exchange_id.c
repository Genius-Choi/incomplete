int nfs4_proc_exchange_id(struct nfs_client *clp, struct rpc_cred *cred)
{
	nfs4_verifier verifier;
	struct nfs41_exchange_id_args args = {
		.client = clp,
		.flags = EXCHGID4_FLAG_SUPP_MOVED_REFER,
	};
	struct nfs41_exchange_id_res res = {
		.client = clp,
	};
	int status;
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_EXCHANGE_ID],
		.rpc_argp = &args,
		.rpc_resp = &res,
		.rpc_cred = cred,
	};
	__be32 *p;

	dprintk("--> %s\n", __func__);
	BUG_ON(clp == NULL);

	p = (u32 *)verifier.data;
	*p++ = htonl((u32)clp->cl_boot_time.tv_sec);
	*p = htonl((u32)clp->cl_boot_time.tv_nsec);
	args.verifier = &verifier;

	args.id_len = scnprintf(args.id, sizeof(args.id),
				"%s/%s.%s/%u",
				clp->cl_ipaddr,
				init_utsname()->nodename,
				init_utsname()->domainname,
				clp->cl_rpcclient->cl_auth->au_flavor);

	res.server_scope = kzalloc(sizeof(struct server_scope), GFP_KERNEL);
	if (unlikely(!res.server_scope))
		return -ENOMEM;

	status = rpc_call_sync(clp->cl_rpcclient, &msg, RPC_TASK_TIMEOUT);
	if (!status)
		status = nfs4_check_cl_exchange_flags(clp->cl_exchange_flags);

	if (!status) {
		if (clp->server_scope &&
		    !nfs41_same_server_scope(clp->server_scope,
					     res.server_scope)) {
			dprintk("%s: server_scope mismatch detected\n",
				__func__);
			set_bit(NFS4CLNT_SERVER_SCOPE_MISMATCH, &clp->cl_state);
			kfree(clp->server_scope);
			clp->server_scope = NULL;
		}

		if (!clp->server_scope)
			clp->server_scope = res.server_scope;
		else
			kfree(res.server_scope);
	}

	dprintk("<-- %s status= %d\n", __func__, status);
	return status;
}
