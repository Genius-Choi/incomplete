static unsigned interleave_nodes(struct mempolicy *policy)
{
	unsigned nid, next;
	struct task_struct *me = current;

	nid = me->il_next;
	next = next_node_in(nid, policy->v.nodes);
	if (next < MAX_NUMNODES)
		me->il_next = next;
	return nid;
}
