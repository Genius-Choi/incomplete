static void mem_cgroup_put(struct mem_cgroup *memcg)
{
	__mem_cgroup_put(memcg, 1);
}
