static int nfs4_do_find_root_sec(struct nfs_server *server,
		struct nfs_fh *fhandle, struct nfs_fsinfo *info)
{
	int mv = server->nfs_client->cl_minorversion;
	return nfs_v4_minor_ops[mv]->find_root_sec(server, fhandle, info);
}
