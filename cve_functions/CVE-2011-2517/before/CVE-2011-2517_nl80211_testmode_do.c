static int nl80211_testmode_do(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	int err;

	if (!info->attrs[NL80211_ATTR_TESTDATA])
		return -EINVAL;

	err = -EOPNOTSUPP;
	if (rdev->ops->testmode_cmd) {
		rdev->testmode_info = info;
		err = rdev->ops->testmode_cmd(&rdev->wiphy,
				nla_data(info->attrs[NL80211_ATTR_TESTDATA]),
				nla_len(info->attrs[NL80211_ATTR_TESTDATA]));
		rdev->testmode_info = NULL;
	}

	return err;
}
