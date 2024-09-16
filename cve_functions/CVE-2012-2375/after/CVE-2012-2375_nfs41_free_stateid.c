static int nfs41_free_stateid(struct nfs_server *server, nfs4_stateid *stateid)
{
	struct nfs4_exception exception = { };
	int err;
	do {
		err = nfs4_handle_exception(server,
				_nfs4_free_stateid(server, stateid),
				&exception);
	} while (exception.retry);
	return err;
}
