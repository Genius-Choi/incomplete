static void nfs4_state_mark_reclaim_helper(struct nfs_client *clp, int (*mark_reclaim)(struct nfs_client *clp, struct nfs4_state *state))
{
	struct nfs4_state_owner *sp;
	struct rb_node *pos;
	struct nfs4_state *state;

	/* Reset all sequence ids to zero */
	for (pos = rb_first(&clp->cl_state_owners); pos != NULL; pos = rb_next(pos)) {
		sp = rb_entry(pos, struct nfs4_state_owner, so_client_node);
		sp->so_seqid.flags = 0;
		spin_lock(&sp->so_lock);
		list_for_each_entry(state, &sp->so_states, open_states) {
			if (mark_reclaim(clp, state))
				nfs4_clear_open_state(state);
		}
		spin_unlock(&sp->so_lock);
	}
}
