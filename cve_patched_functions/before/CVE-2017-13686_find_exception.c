static struct fib_nh_exception *find_exception(struct fib_nh *nh, __be32 daddr)
{
	struct fnhe_hash_bucket *hash = rcu_dereference(nh->nh_exceptions);
	struct fib_nh_exception *fnhe;
	u32 hval;

	if (!hash)
		return NULL;

	hval = fnhe_hashfun(daddr);

	for (fnhe = rcu_dereference(hash[hval].chain); fnhe;
	     fnhe = rcu_dereference(fnhe->fnhe_next)) {
		if (fnhe->fnhe_daddr == daddr)
			return fnhe;
	}
	return NULL;
}
