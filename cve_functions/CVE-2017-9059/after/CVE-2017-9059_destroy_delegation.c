static void destroy_delegation(struct nfs4_delegation *dp)
{
	bool unhashed;

	spin_lock(&state_lock);
	unhashed = unhash_delegation_locked(dp);
	spin_unlock(&state_lock);
	if (unhashed) {
		put_clnt_odstate(dp->dl_clnt_odstate);
		nfs4_put_deleg_lease(dp->dl_stid.sc_file);
		nfs4_put_stid(&dp->dl_stid);
	}
}
