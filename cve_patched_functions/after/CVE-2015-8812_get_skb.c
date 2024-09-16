static struct sk_buff *get_skb(struct sk_buff *skb, int len, gfp_t gfp)
{
	if (skb && !skb_is_nonlinear(skb) && !skb_cloned(skb)) {
		skb_trim(skb, 0);
		skb_get(skb);
	} else {
		skb = alloc_skb(len, gfp);
	}
	return skb;
}
