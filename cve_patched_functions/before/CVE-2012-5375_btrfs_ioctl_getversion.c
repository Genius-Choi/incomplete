static int btrfs_ioctl_getversion(struct file *file, int __user *arg)
{
	struct inode *inode = file->f_path.dentry->d_inode;

	return put_user(inode->i_generation, arg);
}
