void perf_event_free_task(struct task_struct *task)
{
	struct perf_event_context *ctx;
	struct perf_event *event, *tmp;
	int ctxn;

	for_each_task_context_nr(ctxn) {
		ctx = task->perf_event_ctxp[ctxn];
		if (!ctx)
			continue;

		mutex_lock(&ctx->mutex);
again:
		list_for_each_entry_safe(event, tmp, &ctx->pinned_groups,
				group_entry)
			perf_free_event(event, ctx);

		list_for_each_entry_safe(event, tmp, &ctx->flexible_groups,
				group_entry)
			perf_free_event(event, ctx);

		if (!list_empty(&ctx->pinned_groups) ||
				!list_empty(&ctx->flexible_groups))
			goto again;

		mutex_unlock(&ctx->mutex);

		put_ctx(ctx);
	}
}
