static int cpu_clock_sample_group(const clockid_t which_clock,
				  struct task_struct *p,
				  u64 *sample)
{
	struct task_cputime cputime;

	switch (CPUCLOCK_WHICH(which_clock)) {
	default:
		return -EINVAL;
	case CPUCLOCK_PROF:
		thread_group_cputime(p, &cputime);
		*sample = cputime.utime + cputime.stime;
		break;
	case CPUCLOCK_VIRT:
		thread_group_cputime(p, &cputime);
		*sample = cputime.utime;
		break;
	case CPUCLOCK_SCHED:
		thread_group_cputime(p, &cputime);
		*sample = cputime.sum_exec_runtime;
		break;
	}
	return 0;
}
