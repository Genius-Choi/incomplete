static int pg_init_limit_reached(struct multipath *m, struct pgpath *pgpath)
{
	unsigned long flags;
	int limit_reached = 0;

	spin_lock_irqsave(&m->lock, flags);

	if (m->pg_init_count <= m->pg_init_retries)
		m->pg_init_required = 1;
	else
		limit_reached = 1;

	spin_unlock_irqrestore(&m->lock, flags);

	return limit_reached;
}
