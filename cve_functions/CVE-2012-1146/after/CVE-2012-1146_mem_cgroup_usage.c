static inline u64 mem_cgroup_usage(struct mem_cgroup *memcg, bool swap)
{
	u64 val;

	if (!mem_cgroup_is_root(memcg)) {
		if (!swap)
			return res_counter_read_u64(&memcg->res, RES_USAGE);
		else
			return res_counter_read_u64(&memcg->memsw, RES_USAGE);
	}

	val = mem_cgroup_recursive_stat(memcg, MEM_CGROUP_STAT_CACHE);
	val += mem_cgroup_recursive_stat(memcg, MEM_CGROUP_STAT_RSS);

	if (swap)
		val += mem_cgroup_recursive_stat(memcg, MEM_CGROUP_STAT_SWAPOUT);

	return val << PAGE_SHIFT;
}
