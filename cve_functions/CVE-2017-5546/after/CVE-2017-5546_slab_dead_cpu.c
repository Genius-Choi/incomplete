int slab_dead_cpu(unsigned int cpu)
{
	mutex_lock(&slab_mutex);
	cpuup_canceled(cpu);
	mutex_unlock(&slab_mutex);
	return 0;
}
