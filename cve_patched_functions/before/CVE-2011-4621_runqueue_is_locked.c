int runqueue_is_locked(int cpu)
{
	return raw_spin_is_locked(&cpu_rq(cpu)->lock);
}
