static void cleanup_timers_list(struct list_head *head)
{
	struct cpu_timer_list *timer, *next;

	list_for_each_entry_safe(timer, next, head, entry)
		list_del_init(&timer->entry);
}
