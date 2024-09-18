hash_clnt_odstate_locked(struct nfs4_clnt_odstate *co)
{
	struct nfs4_file *fp = co->co_file;

	lockdep_assert_held(&fp->fi_lock);
	list_add(&co->co_perfile, &fp->fi_clnt_odstate);
}
