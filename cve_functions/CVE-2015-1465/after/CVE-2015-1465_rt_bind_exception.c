static bool rt_bind_exception(struct rtable *rt, struct fib_nh_exception *fnhe,
			      __be32 daddr)
{
	bool ret = false;

	spin_lock_bh(&fnhe_lock);

	if (daddr == fnhe->fnhe_daddr) {
		struct rtable __rcu **porig;
		struct rtable *orig;
		int genid = fnhe_genid(dev_net(rt->dst.dev));

		if (rt_is_input_route(rt))
			porig = &fnhe->fnhe_rth_input;
		else
			porig = &fnhe->fnhe_rth_output;
		orig = rcu_dereference(*porig);

		if (fnhe->fnhe_genid != genid) {
			fnhe->fnhe_genid = genid;
			fnhe->fnhe_gw = 0;
			fnhe->fnhe_pmtu = 0;
			fnhe->fnhe_expires = 0;
			fnhe_flush_routes(fnhe);
			orig = NULL;
		}
		fill_route_from_fnhe(rt, fnhe);
		if (!rt->rt_gateway)
			rt->rt_gateway = daddr;

		if (!(rt->dst.flags & DST_NOCACHE)) {
			rcu_assign_pointer(*porig, rt);
			if (orig)
				rt_free(orig);
			ret = true;
		}

		fnhe->fnhe_stamp = jiffies;
	}
	spin_unlock_bh(&fnhe_lock);

	return ret;
}
