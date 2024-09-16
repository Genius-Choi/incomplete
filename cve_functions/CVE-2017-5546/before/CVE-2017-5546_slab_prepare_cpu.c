int slab_prepare_cpu(unsigned int cpu)
{
	int err;

	mutex_lock(&slab_mutex);
	err = cpuup_prepare(cpu);
	mutex_unlock(&slab_mutex);
	return err;
}
