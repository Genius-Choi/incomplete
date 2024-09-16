static inline int task_cputime_expired(const struct task_cputime *sample,
					const struct task_cputime *expires)
{
	if (expires->utime && sample->utime >= expires->utime)
		return 1;
	if (expires->stime && sample->utime + sample->stime >= expires->stime)
		return 1;
	if (expires->sum_exec_runtime != 0 &&
	    sample->sum_exec_runtime >= expires->sum_exec_runtime)
		return 1;
	return 0;
}
