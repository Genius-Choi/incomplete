static void __perf_event_exit_context(void *__info)
{
	struct perf_event_context *ctx = __info;
	struct perf_event *event, *tmp;

	perf_pmu_rotate_stop(ctx->pmu);

	list_for_each_entry_safe(event, tmp, &ctx->pinned_groups, group_entry)
		__perf_remove_from_context(event);
	list_for_each_entry_safe(event, tmp, &ctx->flexible_groups, group_entry)
		__perf_remove_from_context(event);
}
