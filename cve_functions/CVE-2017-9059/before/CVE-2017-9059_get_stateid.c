get_stateid(struct nfsd4_compound_state *cstate, stateid_t *stateid)
{
	if (HAS_STATE_ID(cstate, CURRENT_STATE_ID_FLAG) && CURRENT_STATEID(stateid))
		memcpy(stateid, &cstate->current_stateid, sizeof(stateid_t));
}
