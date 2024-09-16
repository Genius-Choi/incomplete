struct mem_cgroup *parent_mem_cgroup(struct mem_cgroup *memcg)
{
	if (!memcg->res.parent)
		return NULL;
	return mem_cgroup_from_res_counter(memcg->res.parent, res);
}
