void nl80211_send_mgmt_tx_status(struct cfg80211_registered_device *rdev,
				 struct net_device *netdev, u64 cookie,
				 const u8 *buf, size_t len, bool ack,
				 gfp_t gfp)
{
	struct sk_buff *msg;
	void *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	if (!msg)
		return;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_FRAME_TX_STATUS);
	if (!hdr) {
		nlmsg_free(msg);
		return;
	}

	NLA_PUT_U32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx);
	NLA_PUT_U32(msg, NL80211_ATTR_IFINDEX, netdev->ifindex);
	NLA_PUT(msg, NL80211_ATTR_FRAME, len, buf);
	NLA_PUT_U64(msg, NL80211_ATTR_COOKIE, cookie);
	if (ack)
		NLA_PUT_FLAG(msg, NL80211_ATTR_ACK);

	if (genlmsg_end(msg, hdr) < 0) {
		nlmsg_free(msg);
		return;
	}

	genlmsg_multicast(msg, 0, nl80211_mlme_mcgrp.id, gfp);
	return;

 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	nlmsg_free(msg);
}
