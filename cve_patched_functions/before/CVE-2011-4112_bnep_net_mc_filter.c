static inline int bnep_net_mc_filter(struct sk_buff *skb, struct bnep_session *s)
{
	struct ethhdr *eh = (void *) skb->data;

	if ((eh->h_dest[0] & 1) && !test_bit(bnep_mc_hash(eh->h_dest), (ulong *) &s->mc_filter))
		return 1;
	return 0;
}
