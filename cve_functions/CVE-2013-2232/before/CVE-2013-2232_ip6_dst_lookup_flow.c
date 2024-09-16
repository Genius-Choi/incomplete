struct dst_entry *ip6_dst_lookup_flow(struct sock *sk, struct flowi6 *fl6,
				      const struct in6_addr *final_dst,
				      bool can_sleep)
{
	struct dst_entry *dst = NULL;
	int err;

	err = ip6_dst_lookup_tail(sk, &dst, fl6);
	if (err)
		return ERR_PTR(err);
	if (final_dst)
		fl6->daddr = *final_dst;
	if (can_sleep)
		fl6->flowi6_flags |= FLOWI_FLAG_CAN_SLEEP;

	return xfrm_lookup(sock_net(sk), dst, flowi6_to_flowi(fl6), sk, 0);
}
