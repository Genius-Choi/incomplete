static int nl80211_update_mesh_config(struct sk_buff *skb,
				      struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct mesh_config cfg;
	u32 mask;
	int err;

	if (wdev->iftype != NL80211_IFTYPE_MESH_POINT)
		return -EOPNOTSUPP;

	if (!rdev->ops->update_mesh_config)
		return -EOPNOTSUPP;

	err = nl80211_parse_mesh_config(info, &cfg, &mask);
	if (err)
		return err;

	wdev_lock(wdev);
	if (!wdev->mesh_id_len)
		err = -ENOLINK;

	if (!err)
		err = rdev->ops->update_mesh_config(&rdev->wiphy, dev,
						    mask, &cfg);

	wdev_unlock(wdev);

	return err;
}
