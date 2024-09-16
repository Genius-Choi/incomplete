static int macvlan_fill_info(struct sk_buff *skb,
				const struct net_device *dev)
{
	struct macvlan_dev *vlan = netdev_priv(dev);

	NLA_PUT_U32(skb, IFLA_MACVLAN_MODE, vlan->mode);
	return 0;

nla_put_failure:
	return -EMSGSIZE;
}
