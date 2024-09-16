static void migrate_dead_tasks(unsigned int dead_cpu)
{
	struct rq *rq = cpu_rq(dead_cpu);
	struct task_struct *next;

	for ( ; ; ) {
		if (!rq->nr_running)
			break;
		next = pick_next_task(rq);
		if (!next)
			break;
		next->sched_class->put_prev_task(rq, next);
		migrate_dead(dead_cpu, next);

	}
}
