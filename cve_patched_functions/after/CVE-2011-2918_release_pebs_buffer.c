static void release_pebs_buffer(int cpu)
{
	struct debug_store *ds = per_cpu(cpu_hw_events, cpu).ds;

	if (!ds || !x86_pmu.pebs)
		return;

	kfree((void *)(unsigned long)ds->pebs_buffer_base);
	ds->pebs_buffer_base = 0;
}
