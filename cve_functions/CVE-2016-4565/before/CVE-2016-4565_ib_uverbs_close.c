static int ib_uverbs_close(struct inode *inode, struct file *filp)
{
	struct ib_uverbs_file *file = filp->private_data;
	struct ib_uverbs_device *dev = file->device;
	struct ib_ucontext *ucontext = NULL;

	mutex_lock(&file->device->lists_mutex);
	ucontext = file->ucontext;
	file->ucontext = NULL;
	if (!file->is_closed) {
		list_del(&file->list);
		file->is_closed = 1;
	}
	mutex_unlock(&file->device->lists_mutex);
	if (ucontext)
		ib_uverbs_cleanup_ucontext(file, ucontext);

	if (file->async_file)
		kref_put(&file->async_file->ref, ib_uverbs_release_event_file);

	kref_put(&file->ref, ib_uverbs_release_file);
	kobject_put(&dev->kobj);

	return 0;
}
