static u16 ieee80211_netdev_select_queue(struct net_device *dev,
					 struct sk_buff *skb)
{
	return ieee80211_select_queue(IEEE80211_DEV_TO_SUB_IF(dev), skb);
}
