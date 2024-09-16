static void addrconf_dad_start(struct inet6_ifaddr *ifp)
{
	bool begin_dad = false;

	spin_lock_bh(&ifp->state_lock);
	if (ifp->state != INET6_IFADDR_STATE_DEAD) {
		ifp->state = INET6_IFADDR_STATE_PREDAD;
		begin_dad = true;
	}
	spin_unlock_bh(&ifp->state_lock);

	if (begin_dad)
		addrconf_mod_dad_work(ifp, 0);
}
