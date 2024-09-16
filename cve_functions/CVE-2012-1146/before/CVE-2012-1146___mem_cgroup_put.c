static void __mem_cgroup_put(struct mem_cgroup *memcg, int count)
{
	if (atomic_sub_and_test(count, &memcg->refcnt)) {
		struct mem_cgroup *parent = parent_mem_cgroup(memcg);
		__mem_cgroup_free(memcg);
		if (parent)
			mem_cgroup_put(parent);
	}
}
