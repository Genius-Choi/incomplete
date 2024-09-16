static int ksoftirqd_should_run(unsigned int cpu)
{
	return local_softirq_pending();
}
