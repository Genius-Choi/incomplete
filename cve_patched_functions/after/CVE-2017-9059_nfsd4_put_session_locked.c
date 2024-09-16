static void nfsd4_put_session_locked(struct nfsd4_session *ses)
{
	struct nfs4_client *clp = ses->se_client;
	struct nfsd_net *nn = net_generic(clp->net, nfsd_net_id);

	lockdep_assert_held(&nn->client_lock);

	if (atomic_dec_and_test(&ses->se_ref) && is_session_dead(ses))
		free_session(ses);
	put_client_renew_locked(clp);
}
