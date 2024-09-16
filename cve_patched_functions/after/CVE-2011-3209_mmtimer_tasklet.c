static void mmtimer_tasklet(unsigned long data)
{
	int nodeid = data;
	struct mmtimer_node *mn = &timers[nodeid];
	struct mmtimer *x = rb_entry(mn->next, struct mmtimer, list);
	struct k_itimer *t;
	unsigned long flags;

	/* Send signal and deal with periodic signals */
	spin_lock_irqsave(&mn->lock, flags);
	if (!mn->next)
		goto out;

	x = rb_entry(mn->next, struct mmtimer, list);
	t = x->timer;

	if (t->it.mmtimer.clock == TIMER_OFF)
		goto out;

	t->it_overrun = 0;

	mn->next = rb_next(&x->list);
	rb_erase(&x->list, &mn->timer_head);

	if (posix_timer_event(t, 0) != 0)
		t->it_overrun++;

	if(t->it.mmtimer.incr) {
		t->it.mmtimer.expires += t->it.mmtimer.incr;
		mmtimer_add_list(x);
	} else {
		/* Ensure we don't false trigger in mmtimer_interrupt */
		t->it.mmtimer.clock = TIMER_OFF;
		t->it.mmtimer.expires = 0;
		kfree(x);
	}
	/* Set comparator for next timer, if there is one */
	mmtimer_set_next_timer(nodeid);

	t->it_overrun_last = t->it_overrun;
out:
	spin_unlock_irqrestore(&mn->lock, flags);
}
