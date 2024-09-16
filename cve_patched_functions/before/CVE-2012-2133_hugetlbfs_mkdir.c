static int hugetlbfs_mkdir(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	int retval = hugetlbfs_mknod(dir, dentry, mode | S_IFDIR, 0);
	if (!retval)
		inc_nlink(dir);
	return retval;
}
