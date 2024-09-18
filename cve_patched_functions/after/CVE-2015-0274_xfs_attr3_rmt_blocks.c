xfs_attr3_rmt_blocks(
	struct xfs_mount *mp,
	int		attrlen)
{
	if (xfs_sb_version_hascrc(&mp->m_sb)) {
		int buflen = XFS_ATTR3_RMT_BUF_SPACE(mp, mp->m_sb.sb_blocksize);
		return (attrlen + buflen - 1) / buflen;
	}
	return XFS_B_TO_FSB(mp, attrlen);
}
