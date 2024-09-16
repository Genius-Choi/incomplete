nfs4_proc_lookup_mountpoint(struct inode *dir, struct qstr *name,
			    struct nfs_fh *fhandle, struct nfs_fattr *fattr)
{
	struct rpc_clnt *client = NFS_CLIENT(dir);
	int status;

	status = nfs4_proc_lookup_common(&client, dir, name, fhandle, fattr, NULL);
	if (status < 0)
		return ERR_PTR(status);
	return (client == NFS_CLIENT(dir)) ? rpc_clone_client(client) : client;
}
