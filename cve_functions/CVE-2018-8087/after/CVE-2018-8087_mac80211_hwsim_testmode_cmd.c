static int mac80211_hwsim_testmode_cmd(struct ieee80211_hw *hw,
				       struct ieee80211_vif *vif,
				       void *data, int len)
{
	struct mac80211_hwsim_data *hwsim = hw->priv;
	struct nlattr *tb[HWSIM_TM_ATTR_MAX + 1];
	struct sk_buff *skb;
	int err, ps;

	err = nla_parse(tb, HWSIM_TM_ATTR_MAX, data, len,
			hwsim_testmode_policy, NULL);
	if (err)
		return err;

	if (!tb[HWSIM_TM_ATTR_CMD])
		return -EINVAL;

	switch (nla_get_u32(tb[HWSIM_TM_ATTR_CMD])) {
	case HWSIM_TM_CMD_SET_PS:
		if (!tb[HWSIM_TM_ATTR_PS])
			return -EINVAL;
		ps = nla_get_u32(tb[HWSIM_TM_ATTR_PS]);
		return hwsim_fops_ps_write(hwsim, ps);
	case HWSIM_TM_CMD_GET_PS:
		skb = cfg80211_testmode_alloc_reply_skb(hw->wiphy,
						nla_total_size(sizeof(u32)));
		if (!skb)
			return -ENOMEM;
		if (nla_put_u32(skb, HWSIM_TM_ATTR_PS, hwsim->ps))
			goto nla_put_failure;
		return cfg80211_testmode_reply(skb);
	case HWSIM_TM_CMD_STOP_QUEUES:
		ieee80211_stop_queues(hw);
		return 0;
	case HWSIM_TM_CMD_WAKE_QUEUES:
		ieee80211_wake_queues(hw);
		return 0;
	default:
		return -EOPNOTSUPP;
	}

 nla_put_failure:
	kfree_skb(skb);
	return -ENOBUFS;
}
