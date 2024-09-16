static void nfsd4_cstate_assign_replay(struct nfsd4_compound_state *cstate,
		struct nfs4_stateowner *so)
{
	if (!nfsd4_has_session(cstate)) {
		mutex_lock(&so->so_replay.rp_mutex);
		cstate->replay_owner = nfs4_get_stateowner(so);
	}
}
