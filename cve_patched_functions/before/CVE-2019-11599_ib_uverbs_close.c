static int ib_uverbs_close(struct inode *inode, struct file *filp)
{
	struct ib_uverbs_file *file = filp->private_data;

	uverbs_destroy_ufile_hw(file, RDMA_REMOVE_CLOSE);

	mutex_lock(&file->device->lists_mutex);
	list_del_init(&file->list);
	mutex_unlock(&file->device->lists_mutex);

	kref_put(&file->ref, ib_uverbs_release_file);

	return 0;
}
