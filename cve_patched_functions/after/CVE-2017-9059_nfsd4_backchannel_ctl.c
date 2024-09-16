__be32 nfsd4_backchannel_ctl(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate, struct nfsd4_backchannel_ctl *bc)
{
	struct nfsd4_session *session = cstate->session;
	struct nfsd_net *nn = net_generic(SVC_NET(rqstp), nfsd_net_id);
	__be32 status;

	status = nfsd4_check_cb_sec(&bc->bc_cb_sec);
	if (status)
		return status;
	spin_lock(&nn->client_lock);
	session->se_cb_prog = bc->bc_cb_program;
	session->se_cb_sec = bc->bc_cb_sec;
	spin_unlock(&nn->client_lock);

	nfsd4_probe_callback(session->se_client);

	return nfs_ok;
}
