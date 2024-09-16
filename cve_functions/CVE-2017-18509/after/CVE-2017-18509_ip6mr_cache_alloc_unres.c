static struct mfc6_cache *ip6mr_cache_alloc_unres(void)
{
	struct mfc6_cache *c = kmem_cache_zalloc(mrt_cachep, GFP_ATOMIC);
	if (!c)
		return NULL;
	skb_queue_head_init(&c->mfc_un.unres.unresolved);
	c->mfc_un.unres.expires = jiffies + 10 * HZ;
	return c;
}
