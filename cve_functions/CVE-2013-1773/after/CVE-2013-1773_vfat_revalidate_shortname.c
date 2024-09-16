static int vfat_revalidate_shortname(struct dentry *dentry)
{
	int ret = 1;
	spin_lock(&dentry->d_lock);
	if (dentry->d_time != dentry->d_parent->d_inode->i_version)
		ret = 0;
	spin_unlock(&dentry->d_lock);
	return ret;
}
