xfs_attr_node_list(xfs_attr_list_context_t *context)
{
	attrlist_cursor_kern_t *cursor;
	xfs_attr_leafblock_t *leaf;
	xfs_da_intnode_t *node;
	struct xfs_attr3_icleaf_hdr leafhdr;
	struct xfs_da3_icnode_hdr nodehdr;
	struct xfs_da_node_entry *btree;
	int error, i;
	struct xfs_buf *bp;
	struct xfs_inode	*dp = context->dp;
	struct xfs_mount	*mp = dp->i_mount;

	trace_xfs_attr_node_list(context);

	cursor = context->cursor;
	cursor->initted = 1;

	/*
	 * Do all sorts of validation on the passed-in cursor structure.
	 * If anything is amiss, ignore the cursor and look up the hashval
	 * starting from the btree root.
	 */
	bp = NULL;
	if (cursor->blkno > 0) {
		error = xfs_da3_node_read(NULL, dp, cursor->blkno, -1,
					      &bp, XFS_ATTR_FORK);
		if ((error != 0) && (error != -EFSCORRUPTED))
			return error;
		if (bp) {
			struct xfs_attr_leaf_entry *entries;

			node = bp->b_addr;
			switch (be16_to_cpu(node->hdr.info.magic)) {
			case XFS_DA_NODE_MAGIC:
			case XFS_DA3_NODE_MAGIC:
				trace_xfs_attr_list_wrong_blk(context);
				xfs_trans_brelse(NULL, bp);
				bp = NULL;
				break;
			case XFS_ATTR_LEAF_MAGIC:
			case XFS_ATTR3_LEAF_MAGIC:
				leaf = bp->b_addr;
				xfs_attr3_leaf_hdr_from_disk(mp->m_attr_geo,
							     &leafhdr, leaf);
				entries = xfs_attr3_leaf_entryp(leaf);
				if (cursor->hashval > be32_to_cpu(
						entries[leafhdr.count - 1].hashval)) {
					trace_xfs_attr_list_wrong_blk(context);
					xfs_trans_brelse(NULL, bp);
					bp = NULL;
				} else if (cursor->hashval <= be32_to_cpu(
						entries[0].hashval)) {
					trace_xfs_attr_list_wrong_blk(context);
					xfs_trans_brelse(NULL, bp);
					bp = NULL;
				}
				break;
			default:
				trace_xfs_attr_list_wrong_blk(context);
				xfs_trans_brelse(NULL, bp);
				bp = NULL;
			}
		}
	}

	/*
	 * We did not find what we expected given the cursor's contents,
	 * so we start from the top and work down based on the hash value.
	 * Note that start of node block is same as start of leaf block.
	 */
	if (bp == NULL) {
		cursor->blkno = 0;
		for (;;) {
			__uint16_t magic;

			error = xfs_da3_node_read(NULL, dp,
						      cursor->blkno, -1, &bp,
						      XFS_ATTR_FORK);
			if (error)
				return error;
			node = bp->b_addr;
			magic = be16_to_cpu(node->hdr.info.magic);
			if (magic == XFS_ATTR_LEAF_MAGIC ||
			    magic == XFS_ATTR3_LEAF_MAGIC)
				break;
			if (magic != XFS_DA_NODE_MAGIC &&
			    magic != XFS_DA3_NODE_MAGIC) {
				XFS_CORRUPTION_ERROR("xfs_attr_node_list(3)",
						     XFS_ERRLEVEL_LOW,
						     context->dp->i_mount,
						     node);
				xfs_trans_brelse(NULL, bp);
				return -EFSCORRUPTED;
			}

			dp->d_ops->node_hdr_from_disk(&nodehdr, node);
			btree = dp->d_ops->node_tree_p(node);
			for (i = 0; i < nodehdr.count; btree++, i++) {
				if (cursor->hashval
						<= be32_to_cpu(btree->hashval)) {
					cursor->blkno = be32_to_cpu(btree->before);
					trace_xfs_attr_list_node_descend(context,
									 btree);
					break;
				}
			}
			if (i == nodehdr.count) {
				xfs_trans_brelse(NULL, bp);
				return 0;
			}
			xfs_trans_brelse(NULL, bp);
		}
	}
	ASSERT(bp != NULL);

	/*
	 * Roll upward through the blocks, processing each leaf block in
	 * order.  As long as there is space in the result buffer, keep
	 * adding the information.
	 */
	for (;;) {
		leaf = bp->b_addr;
		error = xfs_attr3_leaf_list_int(bp, context);
		if (error) {
			xfs_trans_brelse(NULL, bp);
			return error;
		}
		xfs_attr3_leaf_hdr_from_disk(mp->m_attr_geo, &leafhdr, leaf);
		if (context->seen_enough || leafhdr.forw == 0)
			break;
		cursor->blkno = leafhdr.forw;
		xfs_trans_brelse(NULL, bp);
		error = xfs_attr3_leaf_read(NULL, dp, cursor->blkno, -1, &bp);
		if (error)
			return error;
	}
	xfs_trans_brelse(NULL, bp);
	return 0;
}
