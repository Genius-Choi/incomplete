static void free_event_rcu(struct rcu_head *head)
{
	struct perf_event *event;

	event = container_of(head, struct perf_event, rcu_head);
	if (event->ns)
		put_pid_ns(event->ns);
	perf_event_free_filter(event);
	kfree(event);
}
