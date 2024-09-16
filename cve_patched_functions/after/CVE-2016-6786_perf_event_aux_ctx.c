perf_event_aux_ctx(struct perf_event_context *ctx,
		   perf_event_aux_output_cb output,
		   void *data)
{
	struct perf_event *event;

	list_for_each_entry_rcu(event, &ctx->event_list, event_entry) {
		if (event->state < PERF_EVENT_STATE_INACTIVE)
			continue;
		if (!event_filter_match(event))
			continue;
		output(event, data);
	}
}
