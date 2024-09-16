static int ib_uverbs_event_close(struct inode *inode, struct file *filp)
{
	struct ib_uverbs_event_file *file = filp->private_data;
	struct ib_uverbs_event *entry, *tmp;
	int closed_already = 0;

	mutex_lock(&file->uverbs_file->device->lists_mutex);
	spin_lock_irq(&file->lock);
	closed_already = file->is_closed;
	file->is_closed = 1;
	list_for_each_entry_safe(entry, tmp, &file->event_list, list) {
		if (entry->counter)
			list_del(&entry->obj_list);
		kfree(entry);
	}
	spin_unlock_irq(&file->lock);
	if (!closed_already) {
		list_del(&file->list);
		if (file->is_async)
			ib_unregister_event_handler(&file->uverbs_file->
				event_handler);
	}
	mutex_unlock(&file->uverbs_file->device->lists_mutex);

	kref_put(&file->uverbs_file->ref, ib_uverbs_release_file);
	kref_put(&file->ref, ib_uverbs_release_event_file);

	return 0;
}
