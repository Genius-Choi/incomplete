static void perf_event_task_ctx(struct perf_event_context *ctx,
				  struct perf_task_event *task_event)
{
	struct perf_event *event;

	list_for_each_entry_rcu(event, &ctx->event_list, event_entry) {
		if (perf_event_task_match(event))
			perf_event_task_output(event, task_event);
	}
}
