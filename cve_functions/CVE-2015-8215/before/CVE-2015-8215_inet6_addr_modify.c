static int inet6_addr_modify(struct inet6_ifaddr *ifp, u32 ifa_flags,
			     u32 prefered_lft, u32 valid_lft)
{
	u32 flags;
	clock_t expires;
	unsigned long timeout;
	bool was_managetempaddr;
	bool had_prefixroute;

	ASSERT_RTNL();

	if (!valid_lft || (prefered_lft > valid_lft))
		return -EINVAL;

	if (ifa_flags & IFA_F_MANAGETEMPADDR &&
	    (ifp->flags & IFA_F_TEMPORARY || ifp->prefix_len != 64))
		return -EINVAL;

	timeout = addrconf_timeout_fixup(valid_lft, HZ);
	if (addrconf_finite_timeout(timeout)) {
		expires = jiffies_to_clock_t(timeout * HZ);
		valid_lft = timeout;
		flags = RTF_EXPIRES;
	} else {
		expires = 0;
		flags = 0;
		ifa_flags |= IFA_F_PERMANENT;
	}

	timeout = addrconf_timeout_fixup(prefered_lft, HZ);
	if (addrconf_finite_timeout(timeout)) {
		if (timeout == 0)
			ifa_flags |= IFA_F_DEPRECATED;
		prefered_lft = timeout;
	}

	spin_lock_bh(&ifp->lock);
	was_managetempaddr = ifp->flags & IFA_F_MANAGETEMPADDR;
	had_prefixroute = ifp->flags & IFA_F_PERMANENT &&
			  !(ifp->flags & IFA_F_NOPREFIXROUTE);
	ifp->flags &= ~(IFA_F_DEPRECATED | IFA_F_PERMANENT | IFA_F_NODAD |
			IFA_F_HOMEADDRESS | IFA_F_MANAGETEMPADDR |
			IFA_F_NOPREFIXROUTE);
	ifp->flags |= ifa_flags;
	ifp->tstamp = jiffies;
	ifp->valid_lft = valid_lft;
	ifp->prefered_lft = prefered_lft;

	spin_unlock_bh(&ifp->lock);
	if (!(ifp->flags&IFA_F_TENTATIVE))
		ipv6_ifa_notify(0, ifp);

	if (!(ifa_flags & IFA_F_NOPREFIXROUTE)) {
		addrconf_prefix_route(&ifp->addr, ifp->prefix_len, ifp->idev->dev,
				      expires, flags);
	} else if (had_prefixroute) {
		enum cleanup_prefix_rt_t action;
		unsigned long rt_expires;

		write_lock_bh(&ifp->idev->lock);
		action = check_cleanup_prefix_route(ifp, &rt_expires);
		write_unlock_bh(&ifp->idev->lock);

		if (action != CLEANUP_PREFIX_RT_NOP) {
			cleanup_prefix_route(ifp, rt_expires,
				action == CLEANUP_PREFIX_RT_DEL);
		}
	}

	if (was_managetempaddr || ifp->flags & IFA_F_MANAGETEMPADDR) {
		if (was_managetempaddr && !(ifp->flags & IFA_F_MANAGETEMPADDR))
			valid_lft = prefered_lft = 0;
		manage_tempaddrs(ifp->idev, ifp, valid_lft, prefered_lft,
				 !was_managetempaddr, jiffies);
	}

	addrconf_verify_rtnl();

	return 0;
}
