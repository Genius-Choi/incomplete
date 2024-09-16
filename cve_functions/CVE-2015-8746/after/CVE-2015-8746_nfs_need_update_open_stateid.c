static bool nfs_need_update_open_stateid(struct nfs4_state *state,
		nfs4_stateid *stateid)
{
	if (test_and_set_bit(NFS_OPEN_STATE, &state->flags) == 0)
		return true;
	if (!nfs4_stateid_match_other(stateid, &state->open_stateid)) {
		nfs_test_and_clear_all_open_stateid(state);
		return true;
	}
	if (nfs4_stateid_is_newer(stateid, &state->open_stateid))
		return true;
	return false;
}
