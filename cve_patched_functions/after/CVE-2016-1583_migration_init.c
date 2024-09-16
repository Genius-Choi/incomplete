static int __init migration_init(void)
{
	sched_rq_cpu_starting(smp_processor_id());
	return 0;
}
