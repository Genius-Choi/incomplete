xfs_attr3_leaf_read_verify(
	struct xfs_buf		*bp)
{
	struct xfs_mount	*mp = bp->b_target->bt_mount;

	if (xfs_sb_version_hascrc(&mp->m_sb) &&
	     !xfs_buf_verify_cksum(bp, XFS_ATTR3_LEAF_CRC_OFF))
		xfs_buf_ioerror(bp, EFSBADCRC);
	else if (!xfs_attr3_leaf_verify(bp))
		xfs_buf_ioerror(bp, EFSCORRUPTED);

	if (bp->b_error)
		xfs_verifier_error(bp);
}
