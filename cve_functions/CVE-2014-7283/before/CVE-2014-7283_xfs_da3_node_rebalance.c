xfs_da3_node_rebalance(
	struct xfs_da_state	*state,
	struct xfs_da_state_blk	*blk1,
	struct xfs_da_state_blk	*blk2)
{
	struct xfs_da_intnode	*node1;
	struct xfs_da_intnode	*node2;
	struct xfs_da_intnode	*tmpnode;
	struct xfs_da_node_entry *btree1;
	struct xfs_da_node_entry *btree2;
	struct xfs_da_node_entry *btree_s;
	struct xfs_da_node_entry *btree_d;
	struct xfs_da3_icnode_hdr nodehdr1;
	struct xfs_da3_icnode_hdr nodehdr2;
	struct xfs_trans	*tp;
	int			count;
	int			tmp;
	int			swap = 0;
	struct xfs_inode	*dp = state->args->dp;

	trace_xfs_da_node_rebalance(state->args);

	node1 = blk1->bp->b_addr;
	node2 = blk2->bp->b_addr;
	dp->d_ops->node_hdr_from_disk(&nodehdr1, node1);
	dp->d_ops->node_hdr_from_disk(&nodehdr2, node2);
	btree1 = dp->d_ops->node_tree_p(node1);
	btree2 = dp->d_ops->node_tree_p(node2);

	/*
	 * Figure out how many entries need to move, and in which direction.
	 * Swap the nodes around if that makes it simpler.
	 */
	if (nodehdr1.count > 0 && nodehdr2.count > 0 &&
	    ((be32_to_cpu(btree2[0].hashval) < be32_to_cpu(btree1[0].hashval)) ||
	     (be32_to_cpu(btree2[nodehdr2.count - 1].hashval) <
			be32_to_cpu(btree1[nodehdr1.count - 1].hashval)))) {
		tmpnode = node1;
		node1 = node2;
		node2 = tmpnode;
		dp->d_ops->node_hdr_from_disk(&nodehdr1, node1);
		dp->d_ops->node_hdr_from_disk(&nodehdr2, node2);
		btree1 = dp->d_ops->node_tree_p(node1);
		btree2 = dp->d_ops->node_tree_p(node2);
		swap = 1;
	}

	count = (nodehdr1.count - nodehdr2.count) / 2;
	if (count == 0)
		return;
	tp = state->args->trans;
	/*
	 * Two cases: high-to-low and low-to-high.
	 */
	if (count > 0) {
		/*
		 * Move elements in node2 up to make a hole.
		 */
		tmp = nodehdr2.count;
		if (tmp > 0) {
			tmp *= (uint)sizeof(xfs_da_node_entry_t);
			btree_s = &btree2[0];
			btree_d = &btree2[count];
			memmove(btree_d, btree_s, tmp);
		}

		/*
		 * Move the req'd B-tree elements from high in node1 to
		 * low in node2.
		 */
		nodehdr2.count += count;
		tmp = count * (uint)sizeof(xfs_da_node_entry_t);
		btree_s = &btree1[nodehdr1.count - count];
		btree_d = &btree2[0];
		memcpy(btree_d, btree_s, tmp);
		nodehdr1.count -= count;
	} else {
		/*
		 * Move the req'd B-tree elements from low in node2 to
		 * high in node1.
		 */
		count = -count;
		tmp = count * (uint)sizeof(xfs_da_node_entry_t);
		btree_s = &btree2[0];
		btree_d = &btree1[nodehdr1.count];
		memcpy(btree_d, btree_s, tmp);
		nodehdr1.count += count;

		xfs_trans_log_buf(tp, blk1->bp,
			XFS_DA_LOGRANGE(node1, btree_d, tmp));

		/*
		 * Move elements in node2 down to fill the hole.
		 */
		tmp  = nodehdr2.count - count;
		tmp *= (uint)sizeof(xfs_da_node_entry_t);
		btree_s = &btree2[count];
		btree_d = &btree2[0];
		memmove(btree_d, btree_s, tmp);
		nodehdr2.count -= count;
	}

	/*
	 * Log header of node 1 and all current bits of node 2.
	 */
	dp->d_ops->node_hdr_to_disk(node1, &nodehdr1);
	xfs_trans_log_buf(tp, blk1->bp,
		XFS_DA_LOGRANGE(node1, &node1->hdr, dp->d_ops->node_hdr_size));

	dp->d_ops->node_hdr_to_disk(node2, &nodehdr2);
	xfs_trans_log_buf(tp, blk2->bp,
		XFS_DA_LOGRANGE(node2, &node2->hdr,
				dp->d_ops->node_hdr_size +
				(sizeof(btree2[0]) * nodehdr2.count)));

	/*
	 * Record the last hashval from each block for upward propagation.
	 * (note: don't use the swapped node pointers)
	 */
	if (swap) {
		node1 = blk1->bp->b_addr;
		node2 = blk2->bp->b_addr;
		dp->d_ops->node_hdr_from_disk(&nodehdr1, node1);
		dp->d_ops->node_hdr_from_disk(&nodehdr2, node2);
		btree1 = dp->d_ops->node_tree_p(node1);
		btree2 = dp->d_ops->node_tree_p(node2);
	}
	blk1->hashval = be32_to_cpu(btree1[nodehdr1.count - 1].hashval);
	blk2->hashval = be32_to_cpu(btree2[nodehdr2.count - 1].hashval);

	/*
	 * Adjust the expected index for insertion.
	 */
	if (blk1->index >= nodehdr1.count) {
		blk2->index = blk1->index - nodehdr1.count;
		blk1->index = nodehdr1.count + 1;	/* make it invalid */
	}
}
