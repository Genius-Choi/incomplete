static inline int bnep_net_proto_filter(struct sk_buff *skb, struct bnep_session *s)
{
	u16 proto = bnep_net_eth_proto(skb);
	struct bnep_proto_filter *f = s->proto_filter;
	int i;

	for (i = 0; i < BNEP_MAX_PROTO_FILTERS && f[i].end; i++) {
		if (proto >= f[i].start && proto <= f[i].end)
			return 0;
	}

	BT_DBG("BNEP: filtered skb %p, proto 0x%.4x", skb, proto);
	return 1;
}
