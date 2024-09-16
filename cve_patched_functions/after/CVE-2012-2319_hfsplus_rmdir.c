static int hfsplus_rmdir(struct inode *dir, struct dentry *dentry)
{
	struct hfsplus_sb_info *sbi = HFSPLUS_SB(dir->i_sb);
	struct inode *inode = dentry->d_inode;
	int res;

	if (inode->i_size != 2)
		return -ENOTEMPTY;

	mutex_lock(&sbi->vh_mutex);
	res = hfsplus_delete_cat(inode->i_ino, dir, &dentry->d_name);
	if (res)
		goto out;
	clear_nlink(inode);
	inode->i_ctime = CURRENT_TIME_SEC;
	hfsplus_delete_inode(inode);
	mark_inode_dirty(inode);
out:
	mutex_unlock(&sbi->vh_mutex);
	return res;
}
