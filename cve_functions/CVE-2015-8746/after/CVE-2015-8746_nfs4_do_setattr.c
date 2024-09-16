static int nfs4_do_setattr(struct inode *inode, struct rpc_cred *cred,
			   struct nfs_fattr *fattr, struct iattr *sattr,
			   struct nfs4_state *state, struct nfs4_label *ilabel,
			   struct nfs4_label *olabel)
{
	struct nfs_server *server = NFS_SERVER(inode);
	struct nfs4_exception exception = {
		.state = state,
		.inode = inode,
	};
	int err;
	do {
		err = _nfs4_do_setattr(inode, cred, fattr, sattr, state, ilabel, olabel);
		trace_nfs4_setattr(inode, err);
		switch (err) {
		case -NFS4ERR_OPENMODE:
			if (!(sattr->ia_valid & ATTR_SIZE)) {
				pr_warn_once("NFSv4: server %s is incorrectly "
						"applying open mode checks to "
						"a SETATTR that is not "
						"changing file size.\n",
						server->nfs_client->cl_hostname);
			}
			if (state && !(state->state & FMODE_WRITE)) {
				err = -EBADF;
				if (sattr->ia_valid & ATTR_OPEN)
					err = -EACCES;
				goto out;
			}
		}
		err = nfs4_handle_exception(server, err, &exception);
	} while (exception.retry);
out:
	return err;
}
