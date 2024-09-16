static inline int task_is_waking(struct task_struct *p)
{
	return unlikely(p->state == TASK_WAKING);
}
