void mem_cgroup_cancel_charge_swapin(struct mem_cgroup *memcg)
{
	if (mem_cgroup_disabled())
		return;
	if (!memcg)
		return;
	__mem_cgroup_cancel_charge(memcg, 1);
}
