static int cpu_timer_sample_group(const clockid_t which_clock,
				  struct task_struct *p, u64 *sample)
{
	struct task_cputime cputime;

	thread_group_cputimer(p, &cputime);
	switch (CPUCLOCK_WHICH(which_clock)) {
	default:
		return -EINVAL;
	case CPUCLOCK_PROF:
		*sample = cputime.utime + cputime.stime;
		break;
	case CPUCLOCK_VIRT:
		*sample = cputime.utime;
		break;
	case CPUCLOCK_SCHED:
		*sample = cputime.sum_exec_runtime;
		break;
	}
	return 0;
}
