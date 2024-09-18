__be32 nfsd_readv(struct file *file, loff_t offset, struct kvec *vec, int vlen,
		unsigned long *count)
{
	mm_segment_t oldfs;
	int host_err;

	oldfs = get_fs();
	set_fs(KERNEL_DS);
	host_err = vfs_readv(file, (struct iovec __user *)vec, vlen, &offset, 0);
	set_fs(oldfs);
	return nfsd_finish_read(file, count, host_err);
}
