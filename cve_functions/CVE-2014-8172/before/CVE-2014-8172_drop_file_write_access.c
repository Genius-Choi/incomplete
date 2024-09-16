static void drop_file_write_access(struct file *file)
{
	struct vfsmount *mnt = file->f_path.mnt;
	struct dentry *dentry = file->f_path.dentry;
	struct inode *inode = dentry->d_inode;

	put_write_access(inode);

	if (special_file(inode->i_mode))
		return;
	if (file_check_writeable(file) != 0)
		return;
	__mnt_drop_write(mnt);
	file_release_write(file);
}
