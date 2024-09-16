static int nl80211_flush_pmksa(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];

	if (dev->ieee80211_ptr->iftype != NL80211_IFTYPE_STATION &&
	    dev->ieee80211_ptr->iftype != NL80211_IFTYPE_P2P_CLIENT)
		return -EOPNOTSUPP;

	if (!rdev->ops->flush_pmksa)
		return -EOPNOTSUPP;

	return rdev->ops->flush_pmksa(&rdev->wiphy, dev);
}
