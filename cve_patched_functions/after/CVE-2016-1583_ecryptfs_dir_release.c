static int ecryptfs_dir_release(struct inode *inode, struct file *file)
{
	fput(ecryptfs_file_to_lower(file));
	kmem_cache_free(ecryptfs_file_info_cache,
			ecryptfs_file_to_private(file));
	return 0;
}
