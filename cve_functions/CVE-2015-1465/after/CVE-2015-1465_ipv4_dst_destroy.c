static void ipv4_dst_destroy(struct dst_entry *dst)
{
	struct rtable *rt = (struct rtable *) dst;

	if (!list_empty(&rt->rt_uncached)) {
		spin_lock_bh(&rt_uncached_lock);
		list_del(&rt->rt_uncached);
		spin_unlock_bh(&rt_uncached_lock);
	}
}
