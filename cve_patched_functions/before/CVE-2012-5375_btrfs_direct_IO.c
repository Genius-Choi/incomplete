static ssize_t btrfs_direct_IO(int rw, struct kiocb *iocb,
			const struct iovec *iov, loff_t offset,
			unsigned long nr_segs)
{
	struct file *file = iocb->ki_filp;
	struct inode *inode = file->f_mapping->host;

	if (check_direct_IO(BTRFS_I(inode)->root, rw, iocb, iov,
			    offset, nr_segs))
		return 0;

	return __blockdev_direct_IO(rw, iocb, inode,
		   BTRFS_I(inode)->root->fs_info->fs_devices->latest_bdev,
		   iov, offset, nr_segs, btrfs_get_blocks_direct, NULL,
		   btrfs_submit_direct, 0);
}
