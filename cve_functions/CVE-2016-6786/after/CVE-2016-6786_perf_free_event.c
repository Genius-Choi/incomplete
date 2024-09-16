static void perf_free_event(struct perf_event *event,
			    struct perf_event_context *ctx)
{
	struct perf_event *parent = event->parent;

	if (WARN_ON_ONCE(!parent))
		return;

	mutex_lock(&parent->child_mutex);
	list_del_init(&event->child_list);
	mutex_unlock(&parent->child_mutex);

	put_event(parent);

	raw_spin_lock_irq(&ctx->lock);
	perf_group_detach(event);
	list_del_event(event, ctx);
	raw_spin_unlock_irq(&ctx->lock);
	free_event(event);
}
