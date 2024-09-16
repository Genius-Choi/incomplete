static void mem_cgroup_get(struct mem_cgroup *memcg)
{
	atomic_inc(&memcg->refcnt);
}
