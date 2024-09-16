static int udf_mknod(struct inode *dir, struct dentry *dentry, umode_t mode,
		     dev_t rdev)
{
	struct inode *inode;

	if (!old_valid_dev(rdev))
		return -EINVAL;

	inode = udf_new_inode(dir, mode);
	if (IS_ERR(inode))
		return PTR_ERR(inode);

	init_special_inode(inode, mode, rdev);
	return udf_add_nondir(dentry, inode);
}
