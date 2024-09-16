static loff_t ecryptfs_dir_llseek(struct file *file, loff_t offset, int whence)
{
	return vfs_llseek(ecryptfs_file_to_lower(file), offset, whence);
}
