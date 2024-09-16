static int reinstate_path(struct pgpath *pgpath)
{
	int r = 0;
	unsigned long flags;
	struct multipath *m = pgpath->pg->m;

	spin_lock_irqsave(&m->lock, flags);

	if (pgpath->is_active)
		goto out;

	if (!pgpath->pg->ps.type->reinstate_path) {
		DMWARN("Reinstate path not supported by path selector %s",
		       pgpath->pg->ps.type->name);
		r = -EINVAL;
		goto out;
	}

	r = pgpath->pg->ps.type->reinstate_path(&pgpath->pg->ps, &pgpath->path);
	if (r)
		goto out;

	pgpath->is_active = 1;

	if (!m->nr_valid_paths++ && m->queue_size) {
		m->current_pgpath = NULL;
		queue_work(kmultipathd, &m->process_queued_ios);
	} else if (m->hw_handler_name && (m->current_pg == pgpath->pg)) {
		if (queue_work(kmpath_handlerd, &pgpath->activate_path.work))
			m->pg_init_in_progress++;
	}

	dm_path_uevent(DM_UEVENT_PATH_REINSTATED, m->ti,
		      pgpath->path.dev->name, m->nr_valid_paths);

	schedule_work(&m->trigger_event);

out:
	spin_unlock_irqrestore(&m->lock, flags);

	return r;
}
