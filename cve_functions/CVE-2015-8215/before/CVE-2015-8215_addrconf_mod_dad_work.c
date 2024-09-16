static void addrconf_mod_dad_work(struct inet6_ifaddr *ifp,
				   unsigned long delay)
{
	if (!delayed_work_pending(&ifp->dad_work))
		in6_ifa_hold(ifp);
	mod_delayed_work(addrconf_wq, &ifp->dad_work, delay);
}
