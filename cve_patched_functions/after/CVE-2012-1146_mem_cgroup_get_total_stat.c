mem_cgroup_get_total_stat(struct mem_cgroup *memcg, struct mcs_total_stat *s)
{
	struct mem_cgroup *iter;

	for_each_mem_cgroup_tree(iter, memcg)
		mem_cgroup_get_local_stat(iter, s);
}
