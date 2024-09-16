static int nl80211_del_interface(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];

	if (!rdev->ops->del_virtual_intf)
		return -EOPNOTSUPP;

	return rdev->ops->del_virtual_intf(&rdev->wiphy, dev);
}
