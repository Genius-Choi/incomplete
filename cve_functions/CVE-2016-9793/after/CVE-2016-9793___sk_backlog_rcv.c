int __sk_backlog_rcv(struct sock *sk, struct sk_buff *skb)
{
	int ret;
	unsigned long pflags = current->flags;

	/* these should have been dropped before queueing */
	BUG_ON(!sock_flag(sk, SOCK_MEMALLOC));

	current->flags |= PF_MEMALLOC;
	ret = sk->sk_backlog_rcv(sk, skb);
	tsk_restore_flags(current, pflags, PF_MEMALLOC);

	return ret;
}
