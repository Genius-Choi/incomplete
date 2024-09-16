void perf_event_exit_task(struct task_struct *child)
{
	struct perf_event *event, *tmp;
	int ctxn;

	mutex_lock(&child->perf_event_mutex);
	list_for_each_entry_safe(event, tmp, &child->perf_event_list,
				 owner_entry) {
		list_del_init(&event->owner_entry);

		/*
		 * Ensure the list deletion is visible before we clear
		 * the owner, closes a race against perf_release() where
		 * we need to serialize on the owner->perf_event_mutex.
		 */
		smp_store_release(&event->owner, NULL);
	}
	mutex_unlock(&child->perf_event_mutex);

	for_each_task_context_nr(ctxn)
		perf_event_exit_task_context(child, ctxn);

	/*
	 * The perf_event_exit_task_context calls perf_event_task
	 * with child's task_ctx, which generates EXIT events for
	 * child contexts and sets child->perf_event_ctxp[] to NULL.
	 * At this point we need to send EXIT events to cpu contexts.
	 */
	perf_event_task(child, NULL, 0);
}
