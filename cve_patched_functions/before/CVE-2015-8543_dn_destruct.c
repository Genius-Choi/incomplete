static void dn_destruct(struct sock *sk)
{
	struct dn_scp *scp = DN_SK(sk);

	skb_queue_purge(&scp->data_xmit_queue);
	skb_queue_purge(&scp->other_xmit_queue);
	skb_queue_purge(&scp->other_receive_queue);

	dst_release(rcu_dereference_check(sk->sk_dst_cache, 1));
}
