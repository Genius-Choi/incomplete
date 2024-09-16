static void release_ds_buffer(int cpu)
{
	struct debug_store *ds = per_cpu(cpu_hw_events, cpu).ds;

	if (!ds)
		return;

	per_cpu(cpu_hw_events, cpu).ds = NULL;
	kfree(ds);
}
