static void bond_arp_send(struct net_device *slave_dev, int arp_op, __be32 dest_ip, __be32 src_ip, unsigned short vlan_id)
{
	struct sk_buff *skb;

	pr_debug("arp %d on slave %s: dst %x src %x vid %d\n", arp_op,
		 slave_dev->name, dest_ip, src_ip, vlan_id);

	skb = arp_create(arp_op, ETH_P_ARP, dest_ip, slave_dev, src_ip,
			 NULL, slave_dev->dev_addr, NULL);

	if (!skb) {
		pr_err("ARP packet allocation failed\n");
		return;
	}
	if (vlan_id) {
		skb = vlan_put_tag(skb, vlan_id);
		if (!skb) {
			pr_err("failed to insert VLAN tag\n");
			return;
		}
	}
	arp_xmit(skb);
}
