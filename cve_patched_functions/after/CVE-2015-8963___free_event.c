static void __free_event(struct perf_event *event)
{
	if (!event->parent) {
		if (event->attr.sample_type & PERF_SAMPLE_CALLCHAIN)
			put_callchain_buffers();
	}

	perf_event_free_bpf_prog(event);

	if (event->destroy)
		event->destroy(event);

	if (event->ctx)
		put_ctx(event->ctx);

	if (event->pmu) {
		exclusive_event_destroy(event);
		module_put(event->pmu->module);
	}

	call_rcu(&event->rcu_head, free_event_rcu);
}
