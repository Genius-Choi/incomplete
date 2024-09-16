static void ring_buffer_detach(struct perf_event *event,
			       struct ring_buffer *rb)
{
	unsigned long flags;

	if (list_empty(&event->rb_entry))
		return;

	spin_lock_irqsave(&rb->event_lock, flags);
	list_del_init(&event->rb_entry);
	wake_up_all(&event->waitq);
	spin_unlock_irqrestore(&rb->event_lock, flags);
}
