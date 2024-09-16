static inline int task_current(struct rq *rq, struct task_struct *p)
{
	return rq->curr == p;
}
