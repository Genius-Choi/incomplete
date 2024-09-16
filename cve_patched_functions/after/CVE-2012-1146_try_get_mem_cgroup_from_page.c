struct mem_cgroup *try_get_mem_cgroup_from_page(struct page *page)
{
	struct mem_cgroup *memcg = NULL;
	struct page_cgroup *pc;
	unsigned short id;
	swp_entry_t ent;

	VM_BUG_ON(!PageLocked(page));

	pc = lookup_page_cgroup(page);
	lock_page_cgroup(pc);
	if (PageCgroupUsed(pc)) {
		memcg = pc->mem_cgroup;
		if (memcg && !css_tryget(&memcg->css))
			memcg = NULL;
	} else if (PageSwapCache(page)) {
		ent.val = page_private(page);
		id = lookup_swap_cgroup_id(ent);
		rcu_read_lock();
		memcg = mem_cgroup_lookup(id);
		if (memcg && !css_tryget(&memcg->css))
			memcg = NULL;
		rcu_read_unlock();
	}
	unlock_page_cgroup(pc);
	return memcg;
}
