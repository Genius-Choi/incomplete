static int queue_if_no_path(struct multipath *m, unsigned queue_if_no_path,
			    unsigned save_old_value)
{
	unsigned long flags;

	spin_lock_irqsave(&m->lock, flags);

	if (save_old_value)
		m->saved_queue_if_no_path = m->queue_if_no_path;
	else
		m->saved_queue_if_no_path = queue_if_no_path;
	m->queue_if_no_path = queue_if_no_path;
	if (!m->queue_if_no_path && m->queue_size)
		queue_work(kmultipathd, &m->process_queued_ios);

	spin_unlock_irqrestore(&m->lock, flags);

	return 0;
}
