static int nl80211_add_scan_req(struct sk_buff *msg,
				struct cfg80211_registered_device *rdev)
{
	struct cfg80211_scan_request *req = rdev->scan_req;
	struct nlattr *nest;
	int i;

	ASSERT_RDEV_LOCK(rdev);

	if (WARN_ON(!req))
		return 0;

	nest = nla_nest_start(msg, NL80211_ATTR_SCAN_SSIDS);
	if (!nest)
		goto nla_put_failure;
	for (i = 0; i < req->n_ssids; i++)
		NLA_PUT(msg, i, req->ssids[i].ssid_len, req->ssids[i].ssid);
	nla_nest_end(msg, nest);

	nest = nla_nest_start(msg, NL80211_ATTR_SCAN_FREQUENCIES);
	if (!nest)
		goto nla_put_failure;
	for (i = 0; i < req->n_channels; i++)
		NLA_PUT_U32(msg, i, req->channels[i]->center_freq);
	nla_nest_end(msg, nest);

	if (req->ie)
		NLA_PUT(msg, NL80211_ATTR_IE, req->ie_len, req->ie);

	return 0;
 nla_put_failure:
	return -ENOBUFS;
}
