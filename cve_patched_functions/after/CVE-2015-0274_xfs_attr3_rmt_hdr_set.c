xfs_attr3_rmt_hdr_set(
	struct xfs_mount	*mp,
	void			*ptr,
	xfs_ino_t		ino,
	uint32_t		offset,
	uint32_t		size,
	xfs_daddr_t		bno)
{
	struct xfs_attr3_rmt_hdr *rmt = ptr;

	if (!xfs_sb_version_hascrc(&mp->m_sb))
		return 0;

	rmt->rm_magic = cpu_to_be32(XFS_ATTR3_RMT_MAGIC);
	rmt->rm_offset = cpu_to_be32(offset);
	rmt->rm_bytes = cpu_to_be32(size);
	uuid_copy(&rmt->rm_uuid, &mp->m_sb.sb_uuid);
	rmt->rm_owner = cpu_to_be64(ino);
	rmt->rm_blkno = cpu_to_be64(bno);

	return sizeof(struct xfs_attr3_rmt_hdr);
}
