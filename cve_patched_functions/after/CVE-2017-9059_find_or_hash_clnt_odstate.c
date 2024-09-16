find_or_hash_clnt_odstate(struct nfs4_file *fp, struct nfs4_clnt_odstate *new)
{
	struct nfs4_clnt_odstate *co;
	struct nfs4_client *cl;

	if (!new)
		return NULL;

	cl = new->co_client;

	spin_lock(&fp->fi_lock);
	list_for_each_entry(co, &fp->fi_clnt_odstate, co_perfile) {
		if (co->co_client == cl) {
			get_clnt_odstate(co);
			goto out;
		}
	}
	co = new;
	co->co_file = fp;
	hash_clnt_odstate_locked(new);
out:
	spin_unlock(&fp->fi_lock);
	return co;
}
