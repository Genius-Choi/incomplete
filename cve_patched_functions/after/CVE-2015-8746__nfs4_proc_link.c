static int _nfs4_proc_link(struct inode *inode, struct inode *dir, struct qstr *name)
{
	struct nfs_server *server = NFS_SERVER(inode);
	struct nfs4_link_arg arg = {
		.fh     = NFS_FH(inode),
		.dir_fh = NFS_FH(dir),
		.name   = name,
		.bitmask = server->attr_bitmask,
	};
	struct nfs4_link_res res = {
		.server = server,
		.label = NULL,
	};
	struct rpc_message msg = {
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_LINK],
		.rpc_argp = &arg,
		.rpc_resp = &res,
	};
	int status = -ENOMEM;

	res.fattr = nfs_alloc_fattr();
	if (res.fattr == NULL)
		goto out;

	res.label = nfs4_label_alloc(server, GFP_KERNEL);
	if (IS_ERR(res.label)) {
		status = PTR_ERR(res.label);
		goto out;
	}
	arg.bitmask = nfs4_bitmask(server, res.label);

	status = nfs4_call_sync(server->client, server, &msg, &arg.seq_args, &res.seq_res, 1);
	if (!status) {
		update_changeattr(dir, &res.cinfo);
		status = nfs_post_op_update_inode(inode, res.fattr);
		if (!status)
			nfs_setsecurity(inode, res.fattr, res.label);
	}


	nfs4_label_free(res.label);

out:
	nfs_free_fattr(res.fattr);
	return status;
}
