void mem_cgroup_commit_charge_swapin(struct page *page,
				     struct mem_cgroup *memcg)
{
	__mem_cgroup_commit_charge_swapin(page, memcg,
					  MEM_CGROUP_CHARGE_TYPE_MAPPED);
}
