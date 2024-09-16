static struct dquot **ext4_get_dquots(struct inode *inode)
{
	return EXT4_I(inode)->i_dquot;
}
