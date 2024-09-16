xfs_attr3_rmt_verify(
	struct xfs_mount	*mp,
	void			*ptr,
	int			fsbsize,
	xfs_daddr_t		bno)
{
	struct xfs_attr3_rmt_hdr *rmt = ptr;

	if (!xfs_sb_version_hascrc(&mp->m_sb))
		return false;
	if (rmt->rm_magic != cpu_to_be32(XFS_ATTR3_RMT_MAGIC))
		return false;
	if (!uuid_equal(&rmt->rm_uuid, &mp->m_sb.sb_uuid))
		return false;
	if (be64_to_cpu(rmt->rm_blkno) != bno)
		return false;
	if (be32_to_cpu(rmt->rm_bytes) > fsbsize - sizeof(*rmt))
		return false;
	if (be32_to_cpu(rmt->rm_offset) +
				be32_to_cpu(rmt->rm_bytes) > XATTR_SIZE_MAX)
		return false;
	if (rmt->rm_owner == 0)
		return false;

	return true;
}
