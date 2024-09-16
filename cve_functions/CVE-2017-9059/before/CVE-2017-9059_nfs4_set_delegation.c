nfs4_set_delegation(struct nfs4_client *clp, struct svc_fh *fh,
		    struct nfs4_file *fp, struct nfs4_clnt_odstate *odstate)
{
	int status;
	struct nfs4_delegation *dp;

	if (fp->fi_had_conflict)
		return ERR_PTR(-EAGAIN);

	spin_lock(&state_lock);
	spin_lock(&fp->fi_lock);
	status = nfs4_get_existing_delegation(clp, fp);
	spin_unlock(&fp->fi_lock);
	spin_unlock(&state_lock);

	if (status)
		return ERR_PTR(status);

	dp = alloc_init_deleg(clp, fh, odstate);
	if (!dp)
		return ERR_PTR(-ENOMEM);

	get_nfs4_file(fp);
	spin_lock(&state_lock);
	spin_lock(&fp->fi_lock);
	dp->dl_stid.sc_file = fp;
	if (!fp->fi_deleg_file) {
		spin_unlock(&fp->fi_lock);
		spin_unlock(&state_lock);
		status = nfs4_setlease(dp);
		goto out;
	}
	if (fp->fi_had_conflict) {
		status = -EAGAIN;
		goto out_unlock;
	}
	status = hash_delegation_locked(dp, fp);
out_unlock:
	spin_unlock(&fp->fi_lock);
	spin_unlock(&state_lock);
out:
	if (status) {
		put_clnt_odstate(dp->dl_clnt_odstate);
		nfs4_put_stid(&dp->dl_stid);
		return ERR_PTR(status);
	}
	return dp;
}
