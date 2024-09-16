static int ovl_mkdir(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	return ovl_create_object(dentry, (mode & 07777) | S_IFDIR, 0, NULL);
}
