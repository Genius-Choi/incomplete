int ext4_get_projid(struct inode *inode, kprojid_t *projid)
{
	if (!EXT4_HAS_RO_COMPAT_FEATURE(inode->i_sb, EXT4_FEATURE_RO_COMPAT_PROJECT))
		return -EOPNOTSUPP;
	*projid = EXT4_I(inode)->i_projid;
	return 0;
}
