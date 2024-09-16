static inline u64 prof_ticks(struct task_struct *p)
{
	u64 utime, stime;

	task_cputime(p, &utime, &stime);

	return utime + stime;
}
