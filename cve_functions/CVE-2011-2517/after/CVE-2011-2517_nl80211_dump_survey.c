static int nl80211_dump_survey(struct sk_buff *skb,
			struct netlink_callback *cb)
{
	struct survey_info survey;
	struct cfg80211_registered_device *dev;
	struct net_device *netdev;
	int survey_idx = cb->args[1];
	int res;

	res = nl80211_prepare_netdev_dump(skb, cb, &dev, &netdev);
	if (res)
		return res;

	if (!dev->ops->dump_survey) {
		res = -EOPNOTSUPP;
		goto out_err;
	}

	while (1) {
		res = dev->ops->dump_survey(&dev->wiphy, netdev, survey_idx,
					    &survey);
		if (res == -ENOENT)
			break;
		if (res)
			goto out_err;

		if (nl80211_send_survey(skb,
				NETLINK_CB(cb->skb).pid,
				cb->nlh->nlmsg_seq, NLM_F_MULTI,
				netdev,
				&survey) < 0)
			goto out;
		survey_idx++;
	}

 out:
	cb->args[1] = survey_idx;
	res = skb->len;
 out_err:
	nl80211_finish_netdev_dump(dev);
	return res;
}
