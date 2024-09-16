static inline void skb_orphan_try(struct sk_buff *skb)
{
	if (!skb_tx(skb)->flags)
		skb_orphan(skb);
}
