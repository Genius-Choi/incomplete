static int br_nf_pre_routing_finish(struct sk_buff *skb)
{
	struct net_device *dev = skb->dev;
	struct iphdr *iph = ip_hdr(skb);
	struct nf_bridge_info *nf_bridge = skb->nf_bridge;
	struct rtable *rt;
	int err;

	if (nf_bridge->mask & BRNF_PKT_TYPE) {
		skb->pkt_type = PACKET_OTHERHOST;
		nf_bridge->mask ^= BRNF_PKT_TYPE;
	}
	nf_bridge->mask ^= BRNF_NF_BRIDGE_PREROUTING;
	if (dnat_took_place(skb)) {
		if ((err = ip_route_input(skb, iph->daddr, iph->saddr, iph->tos, dev))) {
			struct in_device *in_dev = __in_dev_get_rcu(dev);

			/* If err equals -EHOSTUNREACH the error is due to a
			 * martian destination or due to the fact that
			 * forwarding is disabled. For most martian packets,
			 * ip_route_output_key() will fail. It won't fail for 2 types of
			 * martian destinations: loopback destinations and destination
			 * 0.0.0.0. In both cases the packet will be dropped because the
			 * destination is the loopback device and not the bridge. */
			if (err != -EHOSTUNREACH || !in_dev || IN_DEV_FORWARD(in_dev))
				goto free_skb;

			rt = ip_route_output(dev_net(dev), iph->daddr, 0,
					     RT_TOS(iph->tos), 0);
			if (!IS_ERR(rt)) {
				/* - Bridged-and-DNAT'ed traffic doesn't
				 *   require ip_forwarding. */
				if (rt->dst.dev == dev) {
					skb_dst_set(skb, &rt->dst);
					goto bridged_dnat;
				}
				ip_rt_put(rt);
			}
free_skb:
			kfree_skb(skb);
			return 0;
		} else {
			if (skb_dst(skb)->dev == dev) {
bridged_dnat:
				skb->dev = nf_bridge->physindev;
				nf_bridge_update_protocol(skb);
				nf_bridge_push_encap_header(skb);
				NF_HOOK_THRESH(NFPROTO_BRIDGE,
					       NF_BR_PRE_ROUTING,
					       skb, skb->dev, NULL,
					       br_nf_pre_routing_finish_bridge,
					       1);
				return 0;
			}
			memcpy(eth_hdr(skb)->h_dest, dev->dev_addr, ETH_ALEN);
			skb->pkt_type = PACKET_HOST;
		}
	} else {
		rt = bridge_parent_rtable(nf_bridge->physindev);
		if (!rt) {
			kfree_skb(skb);
			return 0;
		}
		skb_dst_set_noref(skb, &rt->dst);
	}

	skb->dev = nf_bridge->physindev;
	nf_bridge_update_protocol(skb);
	nf_bridge_push_encap_header(skb);
	NF_HOOK_THRESH(NFPROTO_BRIDGE, NF_BR_PRE_ROUTING, skb, skb->dev, NULL,
		       br_handle_frame_finish, 1);

	return 0;
}
