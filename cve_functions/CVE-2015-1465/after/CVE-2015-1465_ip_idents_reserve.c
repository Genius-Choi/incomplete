u32 ip_idents_reserve(u32 hash, int segs)
{
	struct ip_ident_bucket *bucket = ip_idents + hash % IP_IDENTS_SZ;
	u32 old = ACCESS_ONCE(bucket->stamp32);
	u32 now = (u32)jiffies;
	u32 delta = 0;

	if (old != now && cmpxchg(&bucket->stamp32, old, now) == old)
		delta = prandom_u32_max(now - old);

	return atomic_add_return(segs + delta, &bucket->id) - segs;
}
