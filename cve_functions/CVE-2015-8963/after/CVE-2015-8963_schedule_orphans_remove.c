static void schedule_orphans_remove(struct perf_event_context *ctx)
{
	if (!ctx->task || ctx->orphans_remove_sched || !perf_wq)
		return;

	if (queue_delayed_work(perf_wq, &ctx->orphans_remove, 1)) {
		get_ctx(ctx);
		ctx->orphans_remove_sched = true;
	}
}
