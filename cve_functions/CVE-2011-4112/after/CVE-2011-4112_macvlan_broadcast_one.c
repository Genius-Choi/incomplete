static int macvlan_broadcast_one(struct sk_buff *skb,
				 const struct macvlan_dev *vlan,
				 const struct ethhdr *eth, bool local)
{
	struct net_device *dev = vlan->dev;
	if (!skb)
		return NET_RX_DROP;

	if (local)
		return vlan->forward(dev, skb);

	skb->dev = dev;
	if (!compare_ether_addr_64bits(eth->h_dest,
				       dev->broadcast))
		skb->pkt_type = PACKET_BROADCAST;
	else
		skb->pkt_type = PACKET_MULTICAST;

	return vlan->receive(skb);
}
