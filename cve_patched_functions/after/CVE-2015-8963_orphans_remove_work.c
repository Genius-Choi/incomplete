static void orphans_remove_work(struct work_struct *work)
{
	struct perf_event_context *ctx;
	struct perf_event *event, *tmp;

	ctx = container_of(work, struct perf_event_context,
			   orphans_remove.work);

	mutex_lock(&ctx->mutex);
	list_for_each_entry_safe(event, tmp, &ctx->event_list, event_entry) {
		struct perf_event *parent_event = event->parent;

		if (!is_orphaned_child(event))
			continue;

		perf_remove_from_context(event, true);

		mutex_lock(&parent_event->child_mutex);
		list_del_init(&event->child_list);
		mutex_unlock(&parent_event->child_mutex);

		free_event(event);
		put_event(parent_event);
	}

	raw_spin_lock_irq(&ctx->lock);
	ctx->orphans_remove_sched = false;
	raw_spin_unlock_irq(&ctx->lock);
	mutex_unlock(&ctx->mutex);

	put_ctx(ctx);
}
