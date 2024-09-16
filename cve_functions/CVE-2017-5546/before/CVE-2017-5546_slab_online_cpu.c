static int slab_online_cpu(unsigned int cpu)
{
	start_cpu_timer(cpu);
	return 0;
}
