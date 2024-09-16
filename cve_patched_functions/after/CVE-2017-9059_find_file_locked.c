find_file_locked(struct knfsd_fh *fh, unsigned int hashval)
{
	struct nfs4_file *fp;

	hlist_for_each_entry_rcu(fp, &file_hashtbl[hashval], fi_hash) {
		if (fh_match(&fp->fi_fhandle, fh)) {
			if (atomic_inc_not_zero(&fp->fi_ref))
				return fp;
		}
	}
	return NULL;
}
