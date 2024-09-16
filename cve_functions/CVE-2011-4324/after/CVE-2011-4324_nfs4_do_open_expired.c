static inline int nfs4_do_open_expired(struct nfs_open_context *ctx, struct nfs4_state *state)
{
	struct nfs_server *server = NFS_SERVER(state->inode);
	struct nfs4_exception exception = { };
	int err;

	do {
		err = _nfs4_open_expired(ctx, state);
		if (err == -NFS4ERR_DELAY)
			nfs4_handle_exception(server, err, &exception);
	} while (exception.retry);
	return err;
}
