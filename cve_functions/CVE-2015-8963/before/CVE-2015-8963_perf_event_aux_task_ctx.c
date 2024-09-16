perf_event_aux_task_ctx(perf_event_aux_output_cb output, void *data,
			struct perf_event_context *task_ctx)
{
	rcu_read_lock();
	preempt_disable();
	perf_event_aux_ctx(task_ctx, output, data);
	preempt_enable();
	rcu_read_unlock();
}
