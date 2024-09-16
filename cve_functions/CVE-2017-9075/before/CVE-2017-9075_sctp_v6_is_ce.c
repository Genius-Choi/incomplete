static int sctp_v6_is_ce(const struct sk_buff *skb)
{
	return *((__u32 *)(ipv6_hdr(skb))) & htonl(1 << 20);
}
