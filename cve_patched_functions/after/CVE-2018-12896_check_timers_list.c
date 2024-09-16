check_timers_list(struct list_head *timers,
		  struct list_head *firing,
		  unsigned long long curr)
{
	int maxfire = 20;

	while (!list_empty(timers)) {
		struct cpu_timer_list *t;

		t = list_first_entry(timers, struct cpu_timer_list, entry);

		if (!--maxfire || curr < t->expires)
			return t->expires;

		t->firing = 1;
		list_move_tail(&t->entry, firing);
	}

	return 0;
}
