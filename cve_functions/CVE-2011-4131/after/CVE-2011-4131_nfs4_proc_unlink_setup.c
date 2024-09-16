static void nfs4_proc_unlink_setup(struct rpc_message *msg, struct inode *dir)
{
	struct nfs_server *server = NFS_SERVER(dir);
	struct nfs_removeargs *args = msg->rpc_argp;
	struct nfs_removeres *res = msg->rpc_resp;

	args->bitmask = server->cache_consistency_bitmask;
	res->server = server;
	res->seq_res.sr_slot = NULL;
	msg->rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_REMOVE];
}
