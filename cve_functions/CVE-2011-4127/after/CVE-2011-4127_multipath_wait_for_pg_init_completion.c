static void multipath_wait_for_pg_init_completion(struct multipath *m)
{
	DECLARE_WAITQUEUE(wait, current);
	unsigned long flags;

	add_wait_queue(&m->pg_init_wait, &wait);

	while (1) {
		set_current_state(TASK_UNINTERRUPTIBLE);

		spin_lock_irqsave(&m->lock, flags);
		if (!m->pg_init_in_progress) {
			spin_unlock_irqrestore(&m->lock, flags);
			break;
		}
		spin_unlock_irqrestore(&m->lock, flags);

		io_schedule();
	}
	set_current_state(TASK_RUNNING);

	remove_wait_queue(&m->pg_init_wait, &wait);
}
