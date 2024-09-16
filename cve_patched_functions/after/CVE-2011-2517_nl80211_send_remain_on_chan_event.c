static void nl80211_send_remain_on_chan_event(
	int cmd, struct cfg80211_registered_device *rdev,
	struct net_device *netdev, u64 cookie,
	struct ieee80211_channel *chan,
	enum nl80211_channel_type channel_type,
	unsigned int duration, gfp_t gfp)
{
	struct sk_buff *msg;
	void *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	if (!msg)
		return;

	hdr = nl80211hdr_put(msg, 0, 0, 0, cmd);
	if (!hdr) {
		nlmsg_free(msg);
		return;
	}

	NLA_PUT_U32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx);
	NLA_PUT_U32(msg, NL80211_ATTR_IFINDEX, netdev->ifindex);
	NLA_PUT_U32(msg, NL80211_ATTR_WIPHY_FREQ, chan->center_freq);
	NLA_PUT_U32(msg, NL80211_ATTR_WIPHY_CHANNEL_TYPE, channel_type);
	NLA_PUT_U64(msg, NL80211_ATTR_COOKIE, cookie);

	if (cmd == NL80211_CMD_REMAIN_ON_CHANNEL)
		NLA_PUT_U32(msg, NL80211_ATTR_DURATION, duration);

	if (genlmsg_end(msg, hdr) < 0) {
		nlmsg_free(msg);
		return;
	}

	genlmsg_multicast_netns(wiphy_net(&rdev->wiphy), msg, 0,
				nl80211_mlme_mcgrp.id, gfp);
	return;

 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	nlmsg_free(msg);
}
