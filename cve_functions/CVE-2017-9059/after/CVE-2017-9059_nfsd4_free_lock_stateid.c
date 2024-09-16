nfsd4_free_lock_stateid(stateid_t *stateid, struct nfs4_stid *s)
{
	struct nfs4_ol_stateid *stp = openlockstateid(s);
	__be32 ret;

	mutex_lock(&stp->st_mutex);

	ret = check_stateid_generation(stateid, &s->sc_stateid, 1);
	if (ret)
		goto out;

	ret = nfserr_locks_held;
	if (check_for_locks(stp->st_stid.sc_file,
			    lockowner(stp->st_stateowner)))
		goto out;

	release_lock_stateid(stp);
	ret = nfs_ok;

out:
	mutex_unlock(&stp->st_mutex);
	nfs4_put_stid(s);
	return ret;
}
