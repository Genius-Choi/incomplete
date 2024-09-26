static void ext4_end_io_dio(struct kiocb *iocb, loff_t offset,
			    ssize_t size, void *private)
{
        ext4_io_end_t *io_end = iocb->private;

	/* if not async direct IO just return */
	if (!io_end)
		return;

	ext_debug("ext4_end_io_dio(): io_end 0x%p "
		  "for inode %lu, iocb 0x%p, offset %llu, size %zd\n",
 		  iocb->private, io_end->inode->i_ino, iocb, offset,
		  size);

	iocb->private = NULL;
	io_end->offset = offset;
	io_end->size = size;
	ext4_put_io_end(io_end);
}
