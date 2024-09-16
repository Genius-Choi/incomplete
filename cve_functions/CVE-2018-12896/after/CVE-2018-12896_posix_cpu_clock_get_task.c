static int posix_cpu_clock_get_task(struct task_struct *tsk,
				    const clockid_t which_clock,
				    struct timespec64 *tp)
{
	int err = -EINVAL;
	u64 rtn;

	if (CPUCLOCK_PERTHREAD(which_clock)) {
		if (same_thread_group(tsk, current))
			err = cpu_clock_sample(which_clock, tsk, &rtn);
	} else {
		if (tsk == current || thread_group_leader(tsk))
			err = cpu_clock_sample_group(which_clock, tsk, &rtn);
	}

	if (!err)
		*tp = ns_to_timespec64(rtn);

	return err;
}
