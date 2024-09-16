static int hfsplus_mkdir(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	return hfsplus_mknod(dir, dentry, mode | S_IFDIR, 0);
}
