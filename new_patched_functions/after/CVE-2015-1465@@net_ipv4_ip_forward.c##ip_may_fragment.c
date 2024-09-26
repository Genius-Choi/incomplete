static bool ip_may_fragment(const struct sk_buff *skb)
{
	return unlikely((ip_hdr(skb)->frag_off & htons(IP_DF)) == 0) ||
		skb->ignore_df;
}
