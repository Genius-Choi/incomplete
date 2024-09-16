static void macvlan_broadcast(struct sk_buff *skb,
			      const struct macvlan_port *port,
			      struct net_device *src,
			      enum macvlan_mode mode)
{
	const struct ethhdr *eth = eth_hdr(skb);
	const struct macvlan_dev *vlan;
	struct hlist_node *n;
	struct sk_buff *nskb;
	unsigned int i;
	int err;

	if (skb->protocol == htons(ETH_P_PAUSE))
		return;

	for (i = 0; i < MACVLAN_HASH_SIZE; i++) {
		hlist_for_each_entry_rcu(vlan, n, &port->vlan_hash[i], hlist) {
			if (vlan->dev == src || !(vlan->mode & mode))
				continue;

			nskb = skb_clone(skb, GFP_ATOMIC);
			err = macvlan_broadcast_one(nskb, vlan, eth,
					 mode == MACVLAN_MODE_BRIDGE);
			macvlan_count_rx(vlan, skb->len + ETH_HLEN,
					 err == NET_RX_SUCCESS, 1);
		}
	}
}
