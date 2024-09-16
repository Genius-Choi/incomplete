static inline void net_timestamp_set(struct sk_buff *skb)
{
	skb->tstamp.tv64 = 0;
	if (static_key_false(&netstamp_needed))
		__net_timestamp(skb);
}
