static void _free_event(struct perf_event *event)
{
	irq_work_sync(&event->pending);

	unaccount_event(event);

	if (event->rb) {
		/*
		 * Can happen when we close an event with re-directed output.
		 *
		 * Since we have a 0 refcount, perf_mmap_close() will skip
		 * over us; possibly making our ring_buffer_put() the last.
		 */
		mutex_lock(&event->mmap_mutex);
		ring_buffer_attach(event, NULL);
		mutex_unlock(&event->mmap_mutex);
	}

	if (is_cgroup_event(event))
		perf_detach_cgroup(event);

	if (!event->parent) {
		if (event->attr.sample_type & PERF_SAMPLE_CALLCHAIN)
			put_callchain_buffers();
	}

	perf_event_free_bpf_prog(event);
	perf_addr_filters_splice(event, NULL);
	kfree(event->addr_filters_offs);

	if (event->destroy)
		event->destroy(event);

	if (event->ctx)
		put_ctx(event->ctx);

	exclusive_event_destroy(event);
	module_put(event->pmu->module);

	call_rcu(&event->rcu_head, free_event_rcu);
}
