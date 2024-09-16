static void multipath_resume(struct dm_target *ti)
{
	struct multipath *m = (struct multipath *) ti->private;
	unsigned long flags;

	spin_lock_irqsave(&m->lock, flags);
	m->queue_if_no_path = m->saved_queue_if_no_path;
	spin_unlock_irqrestore(&m->lock, flags);
}
