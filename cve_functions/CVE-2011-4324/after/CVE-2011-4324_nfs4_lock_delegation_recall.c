int nfs4_lock_delegation_recall(struct nfs4_state *state, struct file_lock *fl)
{
	struct nfs_server *server = NFS_SERVER(state->inode);
	struct nfs4_exception exception = { };
	int err;

	err = nfs4_set_lock_state(state, fl);
	if (err != 0)
		goto out;
	do {
		err = _nfs4_do_setlk(state, F_SETLK, fl, 0);
		if (err != -NFS4ERR_DELAY)
			break;
		err = nfs4_handle_exception(server, err, &exception);
	} while (exception.retry);
out:
	return err;
}
