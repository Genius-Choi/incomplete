static int nl80211_tx_mgmt(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct ieee80211_channel *chan;
	enum nl80211_channel_type channel_type = NL80211_CHAN_NO_HT;
	bool channel_type_valid = false;
	u32 freq;
	int err;
	void *hdr;
	u64 cookie;
	struct sk_buff *msg;
	unsigned int wait = 0;
	bool offchan;

	if (!info->attrs[NL80211_ATTR_FRAME] ||
	    !info->attrs[NL80211_ATTR_WIPHY_FREQ])
		return -EINVAL;

	if (!rdev->ops->mgmt_tx)
		return -EOPNOTSUPP;

	if (dev->ieee80211_ptr->iftype != NL80211_IFTYPE_STATION &&
	    dev->ieee80211_ptr->iftype != NL80211_IFTYPE_ADHOC &&
	    dev->ieee80211_ptr->iftype != NL80211_IFTYPE_P2P_CLIENT &&
	    dev->ieee80211_ptr->iftype != NL80211_IFTYPE_AP &&
	    dev->ieee80211_ptr->iftype != NL80211_IFTYPE_AP_VLAN &&
	    dev->ieee80211_ptr->iftype != NL80211_IFTYPE_MESH_POINT &&
	    dev->ieee80211_ptr->iftype != NL80211_IFTYPE_P2P_GO)
		return -EOPNOTSUPP;

	if (info->attrs[NL80211_ATTR_DURATION]) {
		if (!rdev->ops->mgmt_tx_cancel_wait)
			return -EINVAL;
		wait = nla_get_u32(info->attrs[NL80211_ATTR_DURATION]);
	}

	if (info->attrs[NL80211_ATTR_WIPHY_CHANNEL_TYPE]) {
		channel_type = nla_get_u32(
			info->attrs[NL80211_ATTR_WIPHY_CHANNEL_TYPE]);
		if (channel_type != NL80211_CHAN_NO_HT &&
		    channel_type != NL80211_CHAN_HT20 &&
		    channel_type != NL80211_CHAN_HT40PLUS &&
		    channel_type != NL80211_CHAN_HT40MINUS)
			return -EINVAL;
		channel_type_valid = true;
	}

	offchan = info->attrs[NL80211_ATTR_OFFCHANNEL_TX_OK];

	freq = nla_get_u32(info->attrs[NL80211_ATTR_WIPHY_FREQ]);
	chan = rdev_freq_to_chan(rdev, freq, channel_type);
	if (chan == NULL)
		return -EINVAL;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	hdr = nl80211hdr_put(msg, info->snd_pid, info->snd_seq, 0,
			     NL80211_CMD_FRAME);

	if (IS_ERR(hdr)) {
		err = PTR_ERR(hdr);
		goto free_msg;
	}
	err = cfg80211_mlme_mgmt_tx(rdev, dev, chan, offchan, channel_type,
				    channel_type_valid, wait,
				    nla_data(info->attrs[NL80211_ATTR_FRAME]),
				    nla_len(info->attrs[NL80211_ATTR_FRAME]),
				    &cookie);
	if (err)
		goto free_msg;

	NLA_PUT_U64(msg, NL80211_ATTR_COOKIE, cookie);

	genlmsg_end(msg, hdr);
	return genlmsg_reply(msg, info);

 nla_put_failure:
	err = -ENOBUFS;
 free_msg:
	nlmsg_free(msg);
	return err;
}
