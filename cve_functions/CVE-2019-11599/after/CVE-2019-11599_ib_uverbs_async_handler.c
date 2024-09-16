static void ib_uverbs_async_handler(struct ib_uverbs_file *file,
				    __u64 element, __u64 event,
				    struct list_head *obj_list,
				    u32 *counter)
{
	struct ib_uverbs_event *entry;
	unsigned long flags;

	spin_lock_irqsave(&file->async_file->ev_queue.lock, flags);
	if (file->async_file->ev_queue.is_closed) {
		spin_unlock_irqrestore(&file->async_file->ev_queue.lock, flags);
		return;
	}

	entry = kmalloc(sizeof(*entry), GFP_ATOMIC);
	if (!entry) {
		spin_unlock_irqrestore(&file->async_file->ev_queue.lock, flags);
		return;
	}

	entry->desc.async.element    = element;
	entry->desc.async.event_type = event;
	entry->desc.async.reserved   = 0;
	entry->counter               = counter;

	list_add_tail(&entry->list, &file->async_file->ev_queue.event_list);
	if (obj_list)
		list_add_tail(&entry->obj_list, obj_list);
	spin_unlock_irqrestore(&file->async_file->ev_queue.lock, flags);

	wake_up_interruptible(&file->async_file->ev_queue.poll_wait);
	kill_fasync(&file->async_file->ev_queue.async_queue, SIGIO, POLL_IN);
}
