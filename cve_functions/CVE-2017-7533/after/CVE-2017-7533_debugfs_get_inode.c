static struct inode *debugfs_get_inode(struct super_block *sb)
{
	struct inode *inode = new_inode(sb);
	if (inode) {
		inode->i_ino = get_next_ino();
		inode->i_atime = inode->i_mtime =
			inode->i_ctime = current_time(inode);
	}
	return inode;
}
