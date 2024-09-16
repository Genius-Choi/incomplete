int nfs4_proc_bind_conn_to_session(struct nfs_client *clp, struct rpc_cred *cred)
{
	int status;
	struct nfs41_bind_conn_to_session_args args = {
		.client = clp,
		.dir = NFS4_CDFC4_FORE_OR_BOTH,
	};
	struct nfs41_bind_conn_to_session_res res;
	struct rpc_message msg = {
		.rpc_proc =
			&nfs4_procedures[NFSPROC4_CLNT_BIND_CONN_TO_SESSION],
		.rpc_argp = &args,
		.rpc_resp = &res,
		.rpc_cred = cred,
	};

	dprintk("--> %s\n", __func__);

	nfs4_copy_sessionid(&args.sessionid, &clp->cl_session->sess_id);
	if (!(clp->cl_session->flags & SESSION4_BACK_CHAN))
		args.dir = NFS4_CDFC4_FORE;

	status = rpc_call_sync(clp->cl_rpcclient, &msg, RPC_TASK_TIMEOUT);
	trace_nfs4_bind_conn_to_session(clp, status);
	if (status == 0) {
		if (memcmp(res.sessionid.data,
		    clp->cl_session->sess_id.data, NFS4_MAX_SESSIONID_LEN)) {
			dprintk("NFS: %s: Session ID mismatch\n", __func__);
			status = -EIO;
			goto out;
		}
		if ((res.dir & args.dir) != res.dir || res.dir == 0) {
			dprintk("NFS: %s: Unexpected direction from server\n",
				__func__);
			status = -EIO;
			goto out;
		}
		if (res.use_conn_in_rdma_mode != args.use_conn_in_rdma_mode) {
			dprintk("NFS: %s: Server returned RDMA mode = true\n",
				__func__);
			status = -EIO;
			goto out;
		}
	}
out:
	dprintk("<-- %s status= %d\n", __func__, status);
	return status;
}
