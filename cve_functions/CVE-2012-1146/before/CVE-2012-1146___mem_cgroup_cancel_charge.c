static void __mem_cgroup_cancel_charge(struct mem_cgroup *memcg,
				       unsigned int nr_pages)
{
	if (!mem_cgroup_is_root(memcg)) {
		unsigned long bytes = nr_pages * PAGE_SIZE;

		res_counter_uncharge(&memcg->res, bytes);
		if (do_swap_account)
			res_counter_uncharge(&memcg->memsw, bytes);
	}
}
