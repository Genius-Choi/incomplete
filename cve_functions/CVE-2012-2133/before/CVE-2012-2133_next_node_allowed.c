static int next_node_allowed(int nid, nodemask_t *nodes_allowed)
{
	nid = next_node(nid, *nodes_allowed);
	if (nid == MAX_NUMNODES)
		nid = first_node(*nodes_allowed);
	VM_BUG_ON(nid >= MAX_NUMNODES);

	return nid;
}
