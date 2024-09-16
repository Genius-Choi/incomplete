static int nl80211_set_cqm(struct sk_buff *skb, struct genl_info *info)
{
	struct nlattr *attrs[NL80211_ATTR_CQM_MAX + 1];
	struct nlattr *cqm;
	int err;

	cqm = info->attrs[NL80211_ATTR_CQM];
	if (!cqm) {
		err = -EINVAL;
		goto out;
	}

	err = nla_parse_nested(attrs, NL80211_ATTR_CQM_MAX, cqm,
			       nl80211_attr_cqm_policy);
	if (err)
		goto out;

	if (attrs[NL80211_ATTR_CQM_RSSI_THOLD] &&
	    attrs[NL80211_ATTR_CQM_RSSI_HYST]) {
		s32 threshold;
		u32 hysteresis;
		threshold = nla_get_u32(attrs[NL80211_ATTR_CQM_RSSI_THOLD]);
		hysteresis = nla_get_u32(attrs[NL80211_ATTR_CQM_RSSI_HYST]);
		err = nl80211_set_cqm_rssi(info, threshold, hysteresis);
	} else
		err = -EINVAL;

out:
	return err;
}
