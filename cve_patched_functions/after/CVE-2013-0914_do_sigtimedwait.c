int do_sigtimedwait(const sigset_t *which, siginfo_t *info,
			const struct timespec *ts)
{
	struct task_struct *tsk = current;
	long timeout = MAX_SCHEDULE_TIMEOUT;
	sigset_t mask = *which;
	int sig;

	if (ts) {
		if (!timespec_valid(ts))
			return -EINVAL;
		timeout = timespec_to_jiffies(ts);
		/*
		 * We can be close to the next tick, add another one
		 * to ensure we will wait at least the time asked for.
		 */
		if (ts->tv_sec || ts->tv_nsec)
			timeout++;
	}

	/*
	 * Invert the set of allowed signals to get those we want to block.
	 */
	sigdelsetmask(&mask, sigmask(SIGKILL) | sigmask(SIGSTOP));
	signotset(&mask);

	spin_lock_irq(&tsk->sighand->siglock);
	sig = dequeue_signal(tsk, &mask, info);
	if (!sig && timeout) {
		/*
		 * None ready, temporarily unblock those we're interested
		 * while we are sleeping in so that we'll be awakened when
		 * they arrive. Unblocking is always fine, we can avoid
		 * set_current_blocked().
		 */
		tsk->real_blocked = tsk->blocked;
		sigandsets(&tsk->blocked, &tsk->blocked, &mask);
		recalc_sigpending();
		spin_unlock_irq(&tsk->sighand->siglock);

		timeout = schedule_timeout_interruptible(timeout);

		spin_lock_irq(&tsk->sighand->siglock);
		__set_task_blocked(tsk, &tsk->real_blocked);
		siginitset(&tsk->real_blocked, 0);
		sig = dequeue_signal(tsk, &mask, info);
	}
	spin_unlock_irq(&tsk->sighand->siglock);

	if (sig)
		return sig;
	return timeout ? -EINTR : -EAGAIN;
}
