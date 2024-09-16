find_or_add_file(struct nfs4_file *new, struct knfsd_fh *fh)
{
	struct nfs4_file *fp;
	unsigned int hashval = file_hashval(fh);

	rcu_read_lock();
	fp = find_file_locked(fh, hashval);
	rcu_read_unlock();
	if (fp)
		return fp;

	spin_lock(&state_lock);
	fp = find_file_locked(fh, hashval);
	if (likely(fp == NULL)) {
		nfsd4_init_file(fh, hashval, new);
		fp = new;
	}
	spin_unlock(&state_lock);

	return fp;
}
