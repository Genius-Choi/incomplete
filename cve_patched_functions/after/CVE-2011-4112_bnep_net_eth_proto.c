static inline u16 bnep_net_eth_proto(struct sk_buff *skb)
{
	struct ethhdr *eh = (void *) skb->data;
	u16 proto = ntohs(eh->h_proto);

	if (proto >= 1536)
		return proto;

	if (get_unaligned((__be16 *) skb->data) == htons(0xFFFF))
		return ETH_P_802_3;

	return ETH_P_802_2;
}
