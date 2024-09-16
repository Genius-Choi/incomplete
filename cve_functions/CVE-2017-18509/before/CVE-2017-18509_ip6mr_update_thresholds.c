static void ip6mr_update_thresholds(struct mr6_table *mrt, struct mfc6_cache *cache,
				    unsigned char *ttls)
{
	int vifi;

	cache->mfc_un.res.minvif = MAXMIFS;
	cache->mfc_un.res.maxvif = 0;
	memset(cache->mfc_un.res.ttls, 255, MAXMIFS);

	for (vifi = 0; vifi < mrt->maxvif; vifi++) {
		if (MIF_EXISTS(mrt, vifi) &&
		    ttls[vifi] && ttls[vifi] < 255) {
			cache->mfc_un.res.ttls[vifi] = ttls[vifi];
			if (cache->mfc_un.res.minvif > vifi)
				cache->mfc_un.res.minvif = vifi;
			if (cache->mfc_un.res.maxvif <= vifi)
				cache->mfc_un.res.maxvif = vifi + 1;
		}
	}
	cache->mfc_un.res.lastuse = jiffies;
}
