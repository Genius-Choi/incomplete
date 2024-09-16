put_stateid(struct nfsd4_compound_state *cstate, stateid_t *stateid)
{
	if (cstate->minorversion) {
		memcpy(&cstate->current_stateid, stateid, sizeof(stateid_t));
		SET_STATE_ID(cstate, CURRENT_STATE_ID_FLAG);
	}
}
