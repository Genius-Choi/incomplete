static unsigned long mem_cgroup_nr_lru_pages(struct mem_cgroup *memcg,
			unsigned int lru_mask)
{
	int nid;
	u64 total = 0;

	for_each_node_state(nid, N_HIGH_MEMORY)
		total += mem_cgroup_node_nr_lru_pages(memcg, nid, lru_mask);
	return total;
}
