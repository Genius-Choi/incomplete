static int nl80211_tx_mgmt_cancel_wait(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	u64 cookie;

	if (!info->attrs[NL80211_ATTR_COOKIE])
		return -EINVAL;

	if (!rdev->ops->mgmt_tx_cancel_wait)
		return -EOPNOTSUPP;

	if (dev->ieee80211_ptr->iftype != NL80211_IFTYPE_STATION &&
	    dev->ieee80211_ptr->iftype != NL80211_IFTYPE_ADHOC &&
	    dev->ieee80211_ptr->iftype != NL80211_IFTYPE_P2P_CLIENT &&
	    dev->ieee80211_ptr->iftype != NL80211_IFTYPE_AP &&
	    dev->ieee80211_ptr->iftype != NL80211_IFTYPE_AP_VLAN &&
	    dev->ieee80211_ptr->iftype != NL80211_IFTYPE_P2P_GO)
		return -EOPNOTSUPP;

	cookie = nla_get_u64(info->attrs[NL80211_ATTR_COOKIE]);

	return rdev->ops->mgmt_tx_cancel_wait(&rdev->wiphy, dev, cookie);
}
