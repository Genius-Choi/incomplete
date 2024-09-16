static void nf_skb_free(struct sk_buff *skb)
{
	if (NFCT_FRAG6_CB(skb)->orig)
		kfree_skb(NFCT_FRAG6_CB(skb)->orig);
}
