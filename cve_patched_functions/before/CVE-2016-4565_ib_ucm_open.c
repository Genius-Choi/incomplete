static int ib_ucm_open(struct inode *inode, struct file *filp)
{
	struct ib_ucm_file *file;

	file = kmalloc(sizeof(*file), GFP_KERNEL);
	if (!file)
		return -ENOMEM;

	INIT_LIST_HEAD(&file->events);
	INIT_LIST_HEAD(&file->ctxs);
	init_waitqueue_head(&file->poll_wait);

	mutex_init(&file->file_mutex);

	filp->private_data = file;
	file->filp = filp;
	file->device = container_of(inode->i_cdev, struct ib_ucm_device, cdev);

	return nonseekable_open(inode, filp);
}
