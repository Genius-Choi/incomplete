static void memcg_oom_recover(struct mem_cgroup *memcg)
{
	if (memcg && atomic_read(&memcg->under_oom))
		memcg_wakeup_oom(memcg);
}
