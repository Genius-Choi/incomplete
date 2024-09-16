nl80211_send_sched_scan_msg(struct sk_buff *msg,
			    struct cfg80211_registered_device *rdev,
			    struct net_device *netdev,
			    u32 pid, u32 seq, int flags, u32 cmd)
{
	void *hdr;

	hdr = nl80211hdr_put(msg, pid, seq, flags, cmd);
	if (!hdr)
		return -1;

	NLA_PUT_U32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx);
	NLA_PUT_U32(msg, NL80211_ATTR_IFINDEX, netdev->ifindex);

	return genlmsg_end(msg, hdr);

 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}
