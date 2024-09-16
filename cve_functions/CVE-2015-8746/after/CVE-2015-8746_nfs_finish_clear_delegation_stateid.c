static void nfs_finish_clear_delegation_stateid(struct nfs4_state *state)
{
	nfs_remove_bad_delegation(state->inode);
	write_seqlock(&state->seqlock);
	nfs4_stateid_copy(&state->stateid, &state->open_stateid);
	write_sequnlock(&state->seqlock);
	clear_bit(NFS_DELEGATED_STATE, &state->flags);
}
