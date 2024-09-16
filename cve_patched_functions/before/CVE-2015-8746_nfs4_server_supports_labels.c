static inline int nfs4_server_supports_labels(struct nfs_server *server)
{
	return server->caps & NFS_CAP_SECURITY_LABEL;
}
