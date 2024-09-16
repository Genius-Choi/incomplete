static unsigned long cpu_avg_load_per_task(int cpu)
{
	struct rq *rq = cpu_rq(cpu);
	unsigned long nr_running = ACCESS_ONCE(rq->nr_running);

	if (nr_running)
		rq->avg_load_per_task = rq->load.weight / nr_running;
	else
		rq->avg_load_per_task = 0;

	return rq->avg_load_per_task;
}
