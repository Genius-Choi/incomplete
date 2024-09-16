static void rt_add_uncached_list(struct rtable *rt)
{
	spin_lock_bh(&rt_uncached_lock);
	list_add_tail(&rt->rt_uncached, &rt_uncached_list);
	spin_unlock_bh(&rt_uncached_lock);
}
