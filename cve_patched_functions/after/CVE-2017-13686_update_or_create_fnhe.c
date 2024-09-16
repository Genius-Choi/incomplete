static void update_or_create_fnhe(struct fib_nh *nh, __be32 daddr, __be32 gw,
				  u32 pmtu, unsigned long expires)
{
	struct fnhe_hash_bucket *hash;
	struct fib_nh_exception *fnhe;
	struct rtable *rt;
	unsigned int i;
	int depth;
	u32 hval = fnhe_hashfun(daddr);

	spin_lock_bh(&fnhe_lock);

	hash = rcu_dereference(nh->nh_exceptions);
	if (!hash) {
		hash = kzalloc(FNHE_HASH_SIZE * sizeof(*hash), GFP_ATOMIC);
		if (!hash)
			goto out_unlock;
		rcu_assign_pointer(nh->nh_exceptions, hash);
	}

	hash += hval;

	depth = 0;
	for (fnhe = rcu_dereference(hash->chain); fnhe;
	     fnhe = rcu_dereference(fnhe->fnhe_next)) {
		if (fnhe->fnhe_daddr == daddr)
			break;
		depth++;
	}

	if (fnhe) {
		if (gw)
			fnhe->fnhe_gw = gw;
		if (pmtu) {
			fnhe->fnhe_pmtu = pmtu;
			fnhe->fnhe_expires = max(1UL, expires);
		}
		/* Update all cached dsts too */
		rt = rcu_dereference(fnhe->fnhe_rth_input);
		if (rt)
			fill_route_from_fnhe(rt, fnhe);
		rt = rcu_dereference(fnhe->fnhe_rth_output);
		if (rt)
			fill_route_from_fnhe(rt, fnhe);
	} else {
		if (depth > FNHE_RECLAIM_DEPTH)
			fnhe = fnhe_oldest(hash);
		else {
			fnhe = kzalloc(sizeof(*fnhe), GFP_ATOMIC);
			if (!fnhe)
				goto out_unlock;

			fnhe->fnhe_next = hash->chain;
			rcu_assign_pointer(hash->chain, fnhe);
		}
		fnhe->fnhe_genid = fnhe_genid(dev_net(nh->nh_dev));
		fnhe->fnhe_daddr = daddr;
		fnhe->fnhe_gw = gw;
		fnhe->fnhe_pmtu = pmtu;
		fnhe->fnhe_expires = expires;

		/* Exception created; mark the cached routes for the nexthop
		 * stale, so anyone caching it rechecks if this exception
		 * applies to them.
		 */
		rt = rcu_dereference(nh->nh_rth_input);
		if (rt)
			rt->dst.obsolete = DST_OBSOLETE_KILL;

		for_each_possible_cpu(i) {
			struct rtable __rcu **prt;
			prt = per_cpu_ptr(nh->nh_pcpu_rth_output, i);
			rt = rcu_dereference(*prt);
			if (rt)
				rt->dst.obsolete = DST_OBSOLETE_KILL;
		}
	}

	fnhe->fnhe_stamp = jiffies;

out_unlock:
	spin_unlock_bh(&fnhe_lock);
}
