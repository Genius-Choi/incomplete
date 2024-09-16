static netdev_features_t dflt_features_check(const struct sk_buff *skb,
					     struct net_device *dev,
					     netdev_features_t features)
{
	return vlan_features_check(skb, features);
}
