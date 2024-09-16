static int nfs41_open_expired(struct nfs4_state_owner *sp, struct nfs4_state *state)
{
	int status;
	struct nfs_server *server = NFS_SERVER(state->inode);

	status = nfs41_test_stateid(server, state);
	if (status == NFS_OK)
		return 0;
	nfs41_free_stateid(server, state);
	return nfs4_open_expired(sp, state);
}
