blkdev_direct_IO(int rw, struct kiocb *iocb, struct iov_iter *iter,
			loff_t offset)
{
	struct file *file = iocb->ki_filp;
	struct inode *inode = file->f_mapping->host;

	return __blockdev_direct_IO(rw, iocb, inode, I_BDEV(inode), iter,
				    offset, blkdev_get_block,
				    NULL, NULL, 0);
}
