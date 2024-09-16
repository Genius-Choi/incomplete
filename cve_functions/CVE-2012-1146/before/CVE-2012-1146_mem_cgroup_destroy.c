static void mem_cgroup_destroy(struct cgroup_subsys *ss,
				struct cgroup *cont)
{
	struct mem_cgroup *memcg = mem_cgroup_from_cont(cont);

	kmem_cgroup_destroy(ss, cont);

	mem_cgroup_put(memcg);
}
