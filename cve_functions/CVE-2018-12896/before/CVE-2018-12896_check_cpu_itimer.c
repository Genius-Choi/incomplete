static void check_cpu_itimer(struct task_struct *tsk, struct cpu_itimer *it,
			     u64 *expires, u64 cur_time, int signo)
{
	if (!it->expires)
		return;

	if (cur_time >= it->expires) {
		if (it->incr)
			it->expires += it->incr;
		else
			it->expires = 0;

		trace_itimer_expire(signo == SIGPROF ?
				    ITIMER_PROF : ITIMER_VIRTUAL,
				    tsk->signal->leader_pid, cur_time);
		__group_send_sig_info(signo, SEND_SIG_PRIV, tsk);
	}

	if (it->expires && (!*expires || it->expires < *expires))
		*expires = it->expires;
}
