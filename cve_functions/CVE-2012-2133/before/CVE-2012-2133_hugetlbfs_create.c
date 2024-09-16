static int hugetlbfs_create(struct inode *dir, struct dentry *dentry, umode_t mode, struct nameidata *nd)
{
	return hugetlbfs_mknod(dir, dentry, mode | S_IFREG, 0);
}
