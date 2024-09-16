static inline int rt_policy(int policy)
{
	if (unlikely(policy == SCHED_FIFO || policy == SCHED_RR))
		return 1;
	return 0;
}
