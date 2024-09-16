put_nfs4_file(struct nfs4_file *fi)
{
	might_lock(&state_lock);

	if (atomic_dec_and_lock(&fi->fi_ref, &state_lock)) {
		hlist_del_rcu(&fi->fi_hash);
		spin_unlock(&state_lock);
		WARN_ON_ONCE(!list_empty(&fi->fi_clnt_odstate));
		WARN_ON_ONCE(!list_empty(&fi->fi_delegations));
		call_rcu(&fi->fi_rcu, nfsd4_free_file_rcu);
	}
}
