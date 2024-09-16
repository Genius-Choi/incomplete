find_in_sessionid_hashtbl(struct nfs4_sessionid *sessionid, struct net *net,
		__be32 *ret)
{
	struct nfsd4_session *session;
	__be32 status = nfserr_badsession;

	session = __find_in_sessionid_hashtbl(sessionid, net);
	if (!session)
		goto out;
	status = nfsd4_get_session_locked(session);
	if (status)
		session = NULL;
out:
	*ret = status;
	return session;
}
