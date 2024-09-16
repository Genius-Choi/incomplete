static struct sk_buff *alloc_tx(struct atm_vcc *vcc, unsigned int size)
{
	struct sk_buff *skb;
	struct sock *sk = sk_atm(vcc);

	if (sk_wmem_alloc_get(sk) && !atm_may_send(vcc, size)) {
		pr_debug("Sorry: wmem_alloc = %d, size = %d, sndbuf = %d\n",
			 sk_wmem_alloc_get(sk), size, sk->sk_sndbuf);
		return NULL;
	}
	while (!(skb = alloc_skb(size, GFP_KERNEL)))
		schedule();
	pr_debug("%d += %d\n", sk_wmem_alloc_get(sk), skb->truesize);
	atomic_add(skb->truesize, &sk->sk_wmem_alloc);
	return skb;
}
