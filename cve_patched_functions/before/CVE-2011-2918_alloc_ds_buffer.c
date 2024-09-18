static int alloc_ds_buffer(int cpu)
{
	int node = cpu_to_node(cpu);
	struct debug_store *ds;

	ds = kmalloc_node(sizeof(*ds), GFP_KERNEL | __GFP_ZERO, node);
	if (unlikely(!ds))
		return -ENOMEM;

	per_cpu(cpu_hw_events, cpu).ds = ds;

	return 0;
}
