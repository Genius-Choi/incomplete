static bool nfs4_roc(struct inode *inode)
{
	if (!nfs_have_layout(inode))
		return false;
	return pnfs_roc(inode);
}
