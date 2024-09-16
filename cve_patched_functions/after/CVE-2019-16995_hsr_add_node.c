struct hsr_node *hsr_add_node(struct list_head *node_db, unsigned char addr[],
			      u16 seq_out)
{
	struct hsr_node *node;
	unsigned long now;
	int i;

	node = kzalloc(sizeof(*node), GFP_ATOMIC);
	if (!node)
		return NULL;

	ether_addr_copy(node->MacAddressA, addr);

	/* We are only interested in time diffs here, so use current jiffies
	 * as initialization. (0 could trigger an spurious ring error warning).
	 */
	now = jiffies;
	for (i = 0; i < HSR_PT_PORTS; i++)
		node->time_in[i] = now;
	for (i = 0; i < HSR_PT_PORTS; i++)
		node->seq_out[i] = seq_out;

	list_add_tail_rcu(&node->mac_list, node_db);

	return node;
}
