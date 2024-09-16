static int __cpuinit memcg_cpu_hotplug_callback(struct notifier_block *nb,
					unsigned long action,
					void *hcpu)
{
	int cpu = (unsigned long)hcpu;
	struct memcg_stock_pcp *stock;
	struct mem_cgroup *iter;

	if ((action == CPU_ONLINE)) {
		for_each_mem_cgroup(iter)
			synchronize_mem_cgroup_on_move(iter, cpu);
		return NOTIFY_OK;
	}

	if ((action != CPU_DEAD) || action != CPU_DEAD_FROZEN)
		return NOTIFY_OK;

	for_each_mem_cgroup(iter)
		mem_cgroup_drain_pcp_counter(iter, cpu);

	stock = &per_cpu(memcg_stock, cpu);
	drain_stock(stock);
	return NOTIFY_OK;
}
