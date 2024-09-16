static void process_queued_ios(struct work_struct *work)
{
	struct multipath *m =
		container_of(work, struct multipath, process_queued_ios);
	struct pgpath *pgpath = NULL;
	unsigned must_queue = 1;
	unsigned long flags;

	spin_lock_irqsave(&m->lock, flags);

	if (!m->queue_size)
		goto out;

	if (!m->current_pgpath)
		__choose_pgpath(m, 0);

	pgpath = m->current_pgpath;

	if ((pgpath && !m->queue_io) ||
	    (!pgpath && !m->queue_if_no_path))
		must_queue = 0;

	if (m->pg_init_required && !m->pg_init_in_progress && pgpath)
		__pg_init_all_paths(m);

out:
	spin_unlock_irqrestore(&m->lock, flags);
	if (!must_queue)
		dispatch_queued_ios(m);
}
