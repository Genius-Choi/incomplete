xfs_attr_leaf_list(xfs_attr_list_context_t *context)
{
	int error;
	struct xfs_buf *bp;

	trace_xfs_attr_leaf_list(context);

	context->cursor->blkno = 0;
	error = xfs_attr3_leaf_read(NULL, context->dp, 0, -1, &bp);
	if (error)
		return XFS_ERROR(error);

	error = xfs_attr3_leaf_list_int(bp, context);
	xfs_trans_brelse(NULL, bp);
	return XFS_ERROR(error);
}
