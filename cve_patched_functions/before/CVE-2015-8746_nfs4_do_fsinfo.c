static int nfs4_do_fsinfo(struct nfs_server *server, struct nfs_fh *fhandle, struct nfs_fsinfo *fsinfo)
{
	struct nfs4_exception exception = { };
	unsigned long now = jiffies;
	int err;

	do {
		err = _nfs4_do_fsinfo(server, fhandle, fsinfo);
		trace_nfs4_fsinfo(server, fhandle, fsinfo->fattr, err);
		if (err == 0) {
			struct nfs_client *clp = server->nfs_client;

			spin_lock(&clp->cl_lock);
			clp->cl_lease_time = fsinfo->lease_time * HZ;
			clp->cl_last_renewal = now;
			spin_unlock(&clp->cl_lock);
			break;
		}
		err = nfs4_handle_exception(server, err, &exception);
	} while (exception.retry);
	return err;
}
