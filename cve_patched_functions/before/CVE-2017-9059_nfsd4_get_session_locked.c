static __be32 nfsd4_get_session_locked(struct nfsd4_session *ses)
{
	__be32 status;

	if (is_session_dead(ses))
		return nfserr_badsession;
	status = get_client_locked(ses->se_client);
	if (status)
		return status;
	atomic_inc(&ses->se_ref);
	return nfs_ok;
}
