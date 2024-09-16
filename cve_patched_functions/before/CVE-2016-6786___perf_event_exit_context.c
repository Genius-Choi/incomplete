static void __perf_event_exit_context(void *__info)
{
	struct remove_event re = { .detach_group = true };
	struct perf_event_context *ctx = __info;

	perf_pmu_rotate_stop(ctx->pmu);

	rcu_read_lock();
	list_for_each_entry_rcu(re.event, &ctx->event_list, event_entry)
		__perf_remove_from_context(&re);
	rcu_read_unlock();
}
