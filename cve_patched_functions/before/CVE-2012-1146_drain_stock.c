static void drain_stock(struct memcg_stock_pcp *stock)
{
	struct mem_cgroup *old = stock->cached;

	if (stock->nr_pages) {
		unsigned long bytes = stock->nr_pages * PAGE_SIZE;

		res_counter_uncharge(&old->res, bytes);
		if (do_swap_account)
			res_counter_uncharge(&old->memsw, bytes);
		stock->nr_pages = 0;
	}
	stock->cached = NULL;
}
