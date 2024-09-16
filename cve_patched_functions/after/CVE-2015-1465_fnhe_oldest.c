static struct fib_nh_exception *fnhe_oldest(struct fnhe_hash_bucket *hash)
{
	struct fib_nh_exception *fnhe, *oldest;

	oldest = rcu_dereference(hash->chain);
	for (fnhe = rcu_dereference(oldest->fnhe_next); fnhe;
	     fnhe = rcu_dereference(fnhe->fnhe_next)) {
		if (time_before(fnhe->fnhe_stamp, oldest->fnhe_stamp))
			oldest = fnhe;
	}
	fnhe_flush_routes(oldest);
	return oldest;
}
