int perf_event_init_task(struct task_struct *child)
{
	int ctxn, ret;

	memset(child->perf_event_ctxp, 0, sizeof(child->perf_event_ctxp));
	mutex_init(&child->perf_event_mutex);
	INIT_LIST_HEAD(&child->perf_event_list);

	for_each_task_context_nr(ctxn) {
		ret = perf_event_init_context(child, ctxn);
		if (ret)
			return ret;
	}

	return 0;
}
