static int ip_mc_config(struct sock *sk, bool join, const struct in_ifaddr *ifa)
{
	struct ip_mreqn mreq = {
		.imr_multiaddr.s_addr = ifa->ifa_address,
		.imr_ifindex = ifa->ifa_dev->dev->ifindex,
	};
	int ret;

	ASSERT_RTNL();

	lock_sock(sk);
	if (join)
		ret = ip_mc_join_group(sk, &mreq);
	else
		ret = ip_mc_leave_group(sk, &mreq);
	release_sock(sk);

	return ret;
}
