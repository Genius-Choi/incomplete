void nl80211_send_connect_result(struct cfg80211_registered_device *rdev,
				 struct net_device *netdev, const u8 *bssid,
				 const u8 *req_ie, size_t req_ie_len,
				 const u8 *resp_ie, size_t resp_ie_len,
				 u16 status, gfp_t gfp)
{
	struct sk_buff *msg;
	void *hdr;

	msg = nlmsg_new(NLMSG_GOODSIZE, gfp);
	if (!msg)
		return;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_CONNECT);
	if (!hdr) {
		nlmsg_free(msg);
		return;
	}

	NLA_PUT_U32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx);
	NLA_PUT_U32(msg, NL80211_ATTR_IFINDEX, netdev->ifindex);
	if (bssid)
		NLA_PUT(msg, NL80211_ATTR_MAC, ETH_ALEN, bssid);
	NLA_PUT_U16(msg, NL80211_ATTR_STATUS_CODE, status);
	if (req_ie)
		NLA_PUT(msg, NL80211_ATTR_REQ_IE, req_ie_len, req_ie);
	if (resp_ie)
		NLA_PUT(msg, NL80211_ATTR_RESP_IE, resp_ie_len, resp_ie);

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
