static void free_mem_cgroup_per_zone_info(struct mem_cgroup *memcg, int node)
{
	kfree(memcg->info.nodeinfo[node]);
}
