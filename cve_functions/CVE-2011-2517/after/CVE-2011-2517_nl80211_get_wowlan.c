static int nl80211_get_wowlan(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct sk_buff *msg;
	void *hdr;

	if (!rdev->wiphy.wowlan.flags && !rdev->wiphy.wowlan.n_patterns)
		return -EOPNOTSUPP;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	hdr = nl80211hdr_put(msg, info->snd_pid, info->snd_seq, 0,
			     NL80211_CMD_GET_WOWLAN);
	if (!hdr)
		goto nla_put_failure;

	if (rdev->wowlan) {
		struct nlattr *nl_wowlan;

		nl_wowlan = nla_nest_start(msg, NL80211_ATTR_WOWLAN_TRIGGERS);
		if (!nl_wowlan)
			goto nla_put_failure;

		if (rdev->wowlan->any)
			NLA_PUT_FLAG(msg, NL80211_WOWLAN_TRIG_ANY);
		if (rdev->wowlan->disconnect)
			NLA_PUT_FLAG(msg, NL80211_WOWLAN_TRIG_DISCONNECT);
		if (rdev->wowlan->magic_pkt)
			NLA_PUT_FLAG(msg, NL80211_WOWLAN_TRIG_MAGIC_PKT);
		if (rdev->wowlan->n_patterns) {
			struct nlattr *nl_pats, *nl_pat;
			int i, pat_len;

			nl_pats = nla_nest_start(msg,
					NL80211_WOWLAN_TRIG_PKT_PATTERN);
			if (!nl_pats)
				goto nla_put_failure;

			for (i = 0; i < rdev->wowlan->n_patterns; i++) {
				nl_pat = nla_nest_start(msg, i + 1);
				if (!nl_pat)
					goto nla_put_failure;
				pat_len = rdev->wowlan->patterns[i].pattern_len;
				NLA_PUT(msg, NL80211_WOWLAN_PKTPAT_MASK,
					DIV_ROUND_UP(pat_len, 8),
					rdev->wowlan->patterns[i].mask);
				NLA_PUT(msg, NL80211_WOWLAN_PKTPAT_PATTERN,
					pat_len,
					rdev->wowlan->patterns[i].pattern);
				nla_nest_end(msg, nl_pat);
			}
			nla_nest_end(msg, nl_pats);
		}

		nla_nest_end(msg, nl_wowlan);
	}

	genlmsg_end(msg, hdr);
	return genlmsg_reply(msg, info);

nla_put_failure:
	nlmsg_free(msg);
	return -ENOBUFS;
}
