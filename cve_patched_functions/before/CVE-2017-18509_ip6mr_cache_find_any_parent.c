static struct mfc6_cache *ip6mr_cache_find_any_parent(struct mr6_table *mrt,
						      mifi_t mifi)
{
	int line = MFC6_HASH(&in6addr_any, &in6addr_any);
	struct mfc6_cache *c;

	list_for_each_entry(c, &mrt->mfc6_cache_array[line], list)
		if (ipv6_addr_any(&c->mf6c_origin) &&
		    ipv6_addr_any(&c->mf6c_mcastgrp) &&
		    (c->mfc_un.res.ttls[mifi] < 255))
			return c;

	return NULL;
}
