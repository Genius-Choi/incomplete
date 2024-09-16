static void ip_cmsg_recv_pktinfo(struct msghdr *msg, struct sk_buff *skb)
{
	struct in_pktinfo info;
	struct rtable *rt = skb_rtable(skb);

	info.ipi_addr.s_addr = ip_hdr(skb)->daddr;
	if (rt) {
		info.ipi_ifindex = rt->rt_iif;
		info.ipi_spec_dst.s_addr = rt->rt_spec_dst;
	} else {
		info.ipi_ifindex = 0;
		info.ipi_spec_dst.s_addr = 0;
	}

	put_cmsg(msg, SOL_IP, IP_PKTINFO, sizeof(info), &info);
}
