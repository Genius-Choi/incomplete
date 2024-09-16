clear_current_stateid(struct nfsd4_compound_state *cstate)
{
	CLEAR_STATE_ID(cstate, CURRENT_STATE_ID_FLAG);
}
