static int mem_cgroup_pre_destroy(struct cgroup_subsys *ss,
					struct cgroup *cont)
{
	struct mem_cgroup *memcg = mem_cgroup_from_cont(cont);

	return mem_cgroup_force_empty(memcg, false);
}
