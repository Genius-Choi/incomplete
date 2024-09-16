static void l2tp_ip_destroy_sock(struct sock *sk)
{
	struct sk_buff *skb;

	while ((skb = __skb_dequeue_tail(&sk->sk_write_queue)) != NULL)
		kfree_skb(skb);

	sk_refcnt_debug_dec(sk);
}
