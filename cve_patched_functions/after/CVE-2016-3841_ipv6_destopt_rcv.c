static int ipv6_destopt_rcv(struct sk_buff *skb)
{
	struct inet6_skb_parm *opt = IP6CB(skb);
#if IS_ENABLED(CONFIG_IPV6_MIP6)
	__u16 dstbuf;
#endif
	struct dst_entry *dst = skb_dst(skb);

	if (!pskb_may_pull(skb, skb_transport_offset(skb) + 8) ||
	    !pskb_may_pull(skb, (skb_transport_offset(skb) +
				 ((skb_transport_header(skb)[1] + 1) << 3)))) {
		IP6_INC_STATS_BH(dev_net(dst->dev), ip6_dst_idev(dst),
				 IPSTATS_MIB_INHDRERRORS);
		kfree_skb(skb);
		return -1;
	}

	opt->lastopt = opt->dst1 = skb_network_header_len(skb);
#if IS_ENABLED(CONFIG_IPV6_MIP6)
	dstbuf = opt->dst1;
#endif

	if (ip6_parse_tlv(tlvprocdestopt_lst, skb)) {
		skb->transport_header += (skb_transport_header(skb)[1] + 1) << 3;
		opt = IP6CB(skb);
#if IS_ENABLED(CONFIG_IPV6_MIP6)
		opt->nhoff = dstbuf;
#else
		opt->nhoff = opt->dst1;
#endif
		return 1;
	}

	IP6_INC_STATS_BH(dev_net(dst->dev),
			 ip6_dst_idev(dst), IPSTATS_MIB_INHDRERRORS);
	return -1;
}
