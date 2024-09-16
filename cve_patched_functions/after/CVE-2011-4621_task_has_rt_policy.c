static inline int task_has_rt_policy(struct task_struct *p)
{
	return rt_policy(p->policy);
}
