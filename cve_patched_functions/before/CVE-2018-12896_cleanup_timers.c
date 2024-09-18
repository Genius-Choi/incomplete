static void cleanup_timers(struct list_head *head)
{
	cleanup_timers_list(head);
	cleanup_timers_list(++head);
	cleanup_timers_list(++head);
}
