int sched_cpu_starting(unsigned int cpu)
{
	set_cpu_rq_start_time(cpu);
	sched_rq_cpu_starting(cpu);
	return 0;
}
