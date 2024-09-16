xfs_attr3_leaf_write_verify(
	struct xfs_buf	*bp)
{
	struct xfs_mount	*mp = bp->b_target->bt_mount;
	struct xfs_buf_log_item	*bip = bp->b_fspriv;
	struct xfs_attr3_leaf_hdr *hdr3 = bp->b_addr;

	if (!xfs_attr3_leaf_verify(bp)) {
		xfs_buf_ioerror(bp, EFSCORRUPTED);
		xfs_verifier_error(bp);
		return;
	}

	if (!xfs_sb_version_hascrc(&mp->m_sb))
		return;

	if (bip)
		hdr3->info.lsn = cpu_to_be64(bip->bli_item.li_lsn);

	xfs_buf_update_cksum(bp, XFS_ATTR3_LEAF_CRC_OFF);
}
