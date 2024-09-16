static void perf_event_mmap_ctx(struct perf_event_context *ctx,
				  struct perf_mmap_event *mmap_event,
				  int executable)
{
	struct perf_event *event;

	list_for_each_entry_rcu(event, &ctx->event_list, event_entry) {
		if (perf_event_mmap_match(event, mmap_event, executable))
			perf_event_mmap_output(event, mmap_event);
	}
}
