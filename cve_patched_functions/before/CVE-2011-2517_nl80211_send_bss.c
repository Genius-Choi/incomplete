static int nl80211_send_bss(struct sk_buff *msg, u32 pid, u32 seq, int flags,
			    struct cfg80211_registered_device *rdev,
			    struct wireless_dev *wdev,
			    struct cfg80211_internal_bss *intbss)
{
	struct cfg80211_bss *res = &intbss->pub;
	void *hdr;
	struct nlattr *bss;
	int i;

	ASSERT_WDEV_LOCK(wdev);

	hdr = nl80211hdr_put(msg, pid, seq, flags,
			     NL80211_CMD_NEW_SCAN_RESULTS);
	if (!hdr)
		return -1;

	NLA_PUT_U32(msg, NL80211_ATTR_GENERATION, rdev->bss_generation);
	NLA_PUT_U32(msg, NL80211_ATTR_IFINDEX, wdev->netdev->ifindex);

	bss = nla_nest_start(msg, NL80211_ATTR_BSS);
	if (!bss)
		goto nla_put_failure;
	if (!is_zero_ether_addr(res->bssid))
		NLA_PUT(msg, NL80211_BSS_BSSID, ETH_ALEN, res->bssid);
	if (res->information_elements && res->len_information_elements)
		NLA_PUT(msg, NL80211_BSS_INFORMATION_ELEMENTS,
			res->len_information_elements,
			res->information_elements);
	if (res->beacon_ies && res->len_beacon_ies &&
	    res->beacon_ies != res->information_elements)
		NLA_PUT(msg, NL80211_BSS_BEACON_IES,
			res->len_beacon_ies, res->beacon_ies);
	if (res->tsf)
		NLA_PUT_U64(msg, NL80211_BSS_TSF, res->tsf);
	if (res->beacon_interval)
		NLA_PUT_U16(msg, NL80211_BSS_BEACON_INTERVAL, res->beacon_interval);
	NLA_PUT_U16(msg, NL80211_BSS_CAPABILITY, res->capability);
	NLA_PUT_U32(msg, NL80211_BSS_FREQUENCY, res->channel->center_freq);
	NLA_PUT_U32(msg, NL80211_BSS_SEEN_MS_AGO,
		jiffies_to_msecs(jiffies - intbss->ts));

	switch (rdev->wiphy.signal_type) {
	case CFG80211_SIGNAL_TYPE_MBM:
		NLA_PUT_U32(msg, NL80211_BSS_SIGNAL_MBM, res->signal);
		break;
	case CFG80211_SIGNAL_TYPE_UNSPEC:
		NLA_PUT_U8(msg, NL80211_BSS_SIGNAL_UNSPEC, res->signal);
		break;
	default:
		break;
	}

	switch (wdev->iftype) {
	case NL80211_IFTYPE_P2P_CLIENT:
	case NL80211_IFTYPE_STATION:
		if (intbss == wdev->current_bss)
			NLA_PUT_U32(msg, NL80211_BSS_STATUS,
				    NL80211_BSS_STATUS_ASSOCIATED);
		else for (i = 0; i < MAX_AUTH_BSSES; i++) {
			if (intbss != wdev->auth_bsses[i])
				continue;
			NLA_PUT_U32(msg, NL80211_BSS_STATUS,
				    NL80211_BSS_STATUS_AUTHENTICATED);
			break;
		}
		break;
	case NL80211_IFTYPE_ADHOC:
		if (intbss == wdev->current_bss)
			NLA_PUT_U32(msg, NL80211_BSS_STATUS,
				    NL80211_BSS_STATUS_IBSS_JOINED);
		break;
	default:
		break;
	}

	nla_nest_end(msg, bss);

	return genlmsg_end(msg, hdr);

 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}
