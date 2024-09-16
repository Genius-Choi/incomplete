void ip6_datagram_recv_common_ctl(struct sock *sk, struct msghdr *msg,
				 struct sk_buff *skb)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	bool is_ipv6 = skb->protocol == htons(ETH_P_IPV6);

	if (np->rxopt.bits.rxinfo) {
		struct in6_pktinfo src_info;

		if (is_ipv6) {
			src_info.ipi6_ifindex = IP6CB(skb)->iif;
			src_info.ipi6_addr = ipv6_hdr(skb)->daddr;
		} else {
			src_info.ipi6_ifindex =
				PKTINFO_SKB_CB(skb)->ipi_ifindex;
			ipv6_addr_set_v4mapped(ip_hdr(skb)->daddr,
					       &src_info.ipi6_addr);
		}

		if (src_info.ipi6_ifindex >= 0)
			put_cmsg(msg, SOL_IPV6, IPV6_PKTINFO,
				 sizeof(src_info), &src_info);
	}
}
