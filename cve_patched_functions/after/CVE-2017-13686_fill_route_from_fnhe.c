static void fill_route_from_fnhe(struct rtable *rt, struct fib_nh_exception *fnhe)
{
	rt->rt_pmtu = fnhe->fnhe_pmtu;
	rt->dst.expires = fnhe->fnhe_expires;

	if (fnhe->fnhe_gw) {
		rt->rt_flags |= RTCF_REDIRECTED;
		rt->rt_gateway = fnhe->fnhe_gw;
		rt->rt_uses_gateway = 1;
	}
}
