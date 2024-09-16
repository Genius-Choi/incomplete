static ssize_t ext4_direct_IO(int rw, struct kiocb *iocb,
			      const struct iovec *iov, loff_t offset,
			      unsigned long nr_segs)
{
	struct file *file = iocb->ki_filp;
	struct inode *inode = file->f_mapping->host;

	if (EXT4_I(inode)->i_flags & EXT4_EXTENTS_FL)
		return ext4_ext_direct_IO(rw, iocb, iov, offset, nr_segs);

	return ext4_ind_direct_IO(rw, iocb, iov, offset, nr_segs);
}
