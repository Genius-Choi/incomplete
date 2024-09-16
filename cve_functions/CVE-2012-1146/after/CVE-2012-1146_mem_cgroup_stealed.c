static bool mem_cgroup_stealed(struct mem_cgroup *memcg)
{
	VM_BUG_ON(!rcu_read_lock_held());
	return this_cpu_read(memcg->stat->count[MEM_CGROUP_ON_MOVE]) > 0;
}
