static void perf_event_comm_ctx(struct perf_event_context *ctx,
				  struct perf_comm_event *comm_event)
{
	struct perf_event *event;

	list_for_each_entry_rcu(event, &ctx->event_list, event_entry) {
		if (perf_event_comm_match(event))
			perf_event_comm_output(event, comm_event);
	}
}
