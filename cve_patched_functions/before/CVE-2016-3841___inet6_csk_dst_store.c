void __inet6_csk_dst_store(struct sock *sk, struct dst_entry *dst,
			   const struct in6_addr *daddr,
			   const struct in6_addr *saddr)
{
	__ip6_dst_store(sk, dst, daddr, saddr);
}
