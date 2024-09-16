int ip6_dst_lookup(struct sock *sk, struct dst_entry **dst, struct flowi6 *fl6)
{
	*dst = NULL;
	return ip6_dst_lookup_tail(sk, dst, fl6);
}
