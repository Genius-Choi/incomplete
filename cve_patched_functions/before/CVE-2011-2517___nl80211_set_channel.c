static int __nl80211_set_channel(struct cfg80211_registered_device *rdev,
				 struct wireless_dev *wdev,
				 struct genl_info *info)
{
	enum nl80211_channel_type channel_type = NL80211_CHAN_NO_HT;
	u32 freq;
	int result;

	if (!info->attrs[NL80211_ATTR_WIPHY_FREQ])
		return -EINVAL;

	if (!nl80211_can_set_dev_channel(wdev))
		return -EOPNOTSUPP;

	if (info->attrs[NL80211_ATTR_WIPHY_CHANNEL_TYPE]) {
		channel_type = nla_get_u32(info->attrs[
				   NL80211_ATTR_WIPHY_CHANNEL_TYPE]);
		if (channel_type != NL80211_CHAN_NO_HT &&
		    channel_type != NL80211_CHAN_HT20 &&
		    channel_type != NL80211_CHAN_HT40PLUS &&
		    channel_type != NL80211_CHAN_HT40MINUS)
			return -EINVAL;
	}

	freq = nla_get_u32(info->attrs[NL80211_ATTR_WIPHY_FREQ]);

	mutex_lock(&rdev->devlist_mtx);
	if (wdev) {
		wdev_lock(wdev);
		result = cfg80211_set_freq(rdev, wdev, freq, channel_type);
		wdev_unlock(wdev);
	} else {
		result = cfg80211_set_freq(rdev, NULL, freq, channel_type);
	}
	mutex_unlock(&rdev->devlist_mtx);

	return result;
}
