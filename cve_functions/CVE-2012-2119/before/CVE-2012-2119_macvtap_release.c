static int macvtap_release(struct inode *inode, struct file *file)
{
	struct macvtap_queue *q = file->private_data;
	macvtap_put_queue(q);
	return 0;
}
