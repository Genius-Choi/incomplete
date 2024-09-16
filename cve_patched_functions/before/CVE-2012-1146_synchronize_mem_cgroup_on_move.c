static void synchronize_mem_cgroup_on_move(struct mem_cgroup *memcg, int cpu)
{
	int idx = MEM_CGROUP_ON_MOVE;

	spin_lock(&memcg->pcp_counter_lock);
	per_cpu(memcg->stat->count[idx], cpu) = memcg->nocpu_base.count[idx];
	spin_unlock(&memcg->pcp_counter_lock);
}
