static inline void sample_cputime_atomic(struct task_cputime *times,
					 struct task_cputime_atomic *atomic_times)
{
	times->utime = atomic64_read(&atomic_times->utime);
	times->stime = atomic64_read(&atomic_times->stime);
	times->sum_exec_runtime = atomic64_read(&atomic_times->sum_exec_runtime);
}
