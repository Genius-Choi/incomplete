struct rpc_clnt *rpc_bind_new_program(struct rpc_clnt *old,
				      struct rpc_program *program,
				      u32 vers)
{
	struct rpc_clnt *clnt;
	struct rpc_version *version;
	int err;

	BUG_ON(vers >= program->nrvers || !program->version[vers]);
	version = program->version[vers];
	clnt = rpc_clone_client(old);
	if (IS_ERR(clnt))
		goto out;
	clnt->cl_procinfo = version->procs;
	clnt->cl_maxproc  = version->nrprocs;
	clnt->cl_protname = program->name;
	clnt->cl_prog     = program->number;
	clnt->cl_vers     = version->number;
	clnt->cl_stats    = program->stats;
	err = rpc_ping(clnt);
	if (err != 0) {
		rpc_shutdown_client(clnt);
		clnt = ERR_PTR(err);
	}
out:
	return clnt;
}
