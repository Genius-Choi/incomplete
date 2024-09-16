static int ip6_tnl_rcv(struct sk_buff *skb, __u16 protocol,
		       __u8 ipproto,
		       void (*dscp_ecn_decapsulate)(struct ip6_tnl *t,
						    struct ipv6hdr *ipv6h,
						    struct sk_buff *skb))
{
	struct ip6_tnl *t;
	struct ipv6hdr *ipv6h = ipv6_hdr(skb);

	rcu_read_lock();

	if ((t = ip6_tnl_lookup(dev_net(skb->dev), &ipv6h->saddr,
					&ipv6h->daddr)) != NULL) {
		if (t->parms.proto != ipproto && t->parms.proto != 0) {
			rcu_read_unlock();
			goto discard;
		}

		if (!xfrm6_policy_check(NULL, XFRM_POLICY_IN, skb)) {
			rcu_read_unlock();
			goto discard;
		}

		if (!ip6_tnl_rcv_ctl(t)) {
			t->dev->stats.rx_dropped++;
			rcu_read_unlock();
			goto discard;
		}
		secpath_reset(skb);
		skb->mac_header = skb->network_header;
		skb_reset_network_header(skb);
		skb->protocol = htons(protocol);
		skb->pkt_type = PACKET_HOST;
		memset(skb->cb, 0, sizeof(struct inet6_skb_parm));
		skb->dev = t->dev;
		skb_dst_drop(skb);
		nf_reset(skb);

		dscp_ecn_decapsulate(t, ipv6h, skb);

		t->dev->stats.rx_packets++;
		t->dev->stats.rx_bytes += skb->len;
		netif_rx(skb);
		rcu_read_unlock();
		return 0;
	}
	rcu_read_unlock();
	return 1;

discard:
	kfree_skb(skb);
	return 0;
}
