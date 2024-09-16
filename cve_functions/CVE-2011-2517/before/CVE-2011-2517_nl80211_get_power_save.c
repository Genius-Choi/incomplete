static int nl80211_get_power_save(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	enum nl80211_ps_state ps_state;
	struct wireless_dev *wdev;
	struct net_device *dev = info->user_ptr[1];
	struct sk_buff *msg;
	void *hdr;
	int err;

	wdev = dev->ieee80211_ptr;

	if (!rdev->ops->set_power_mgmt)
		return -EOPNOTSUPP;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	hdr = nl80211hdr_put(msg, info->snd_pid, info->snd_seq, 0,
			     NL80211_CMD_GET_POWER_SAVE);
	if (!hdr) {
		err = -ENOBUFS;
		goto free_msg;
	}

	if (wdev->ps)
		ps_state = NL80211_PS_ENABLED;
	else
		ps_state = NL80211_PS_DISABLED;

	NLA_PUT_U32(msg, NL80211_ATTR_PS_STATE, ps_state);

	genlmsg_end(msg, hdr);
	return genlmsg_reply(msg, info);

 nla_put_failure:
	err = -ENOBUFS;
 free_msg:
	nlmsg_free(msg);
	return err;
}
