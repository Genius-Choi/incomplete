static int nl80211_msg_put_channel(struct sk_buff *msg,
				   struct ieee80211_channel *chan)
{
	NLA_PUT_U32(msg, NL80211_FREQUENCY_ATTR_FREQ,
		    chan->center_freq);

	if (chan->flags & IEEE80211_CHAN_DISABLED)
		NLA_PUT_FLAG(msg, NL80211_FREQUENCY_ATTR_DISABLED);
	if (chan->flags & IEEE80211_CHAN_PASSIVE_SCAN)
		NLA_PUT_FLAG(msg, NL80211_FREQUENCY_ATTR_PASSIVE_SCAN);
	if (chan->flags & IEEE80211_CHAN_NO_IBSS)
		NLA_PUT_FLAG(msg, NL80211_FREQUENCY_ATTR_NO_IBSS);
	if (chan->flags & IEEE80211_CHAN_RADAR)
		NLA_PUT_FLAG(msg, NL80211_FREQUENCY_ATTR_RADAR);

	NLA_PUT_U32(msg, NL80211_FREQUENCY_ATTR_MAX_TX_POWER,
		    DBM_TO_MBM(chan->max_power));

	return 0;

 nla_put_failure:
	return -ENOBUFS;
}
