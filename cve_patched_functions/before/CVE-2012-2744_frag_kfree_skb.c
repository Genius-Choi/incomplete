static inline void frag_kfree_skb(struct sk_buff *skb, unsigned int *work)
{
	if (work)
		*work -= skb->truesize;
	atomic_sub(skb->truesize, &nf_init_frags.mem);
	nf_skb_free(skb);
	kfree_skb(skb);
}
