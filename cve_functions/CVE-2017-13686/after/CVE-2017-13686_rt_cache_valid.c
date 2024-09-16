static bool rt_cache_valid(const struct rtable *rt)
{
	return	rt &&
		rt->dst.obsolete == DST_OBSOLETE_FORCE_CHK &&
		!rt_is_expired(rt);
}
