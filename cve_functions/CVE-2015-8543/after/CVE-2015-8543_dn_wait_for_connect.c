static struct sk_buff *dn_wait_for_connect(struct sock *sk, long *timeo)
{
	DEFINE_WAIT(wait);
	struct sk_buff *skb = NULL;
	int err = 0;

	prepare_to_wait(sk_sleep(sk), &wait, TASK_INTERRUPTIBLE);
	for(;;) {
		release_sock(sk);
		skb = skb_dequeue(&sk->sk_receive_queue);
		if (skb == NULL) {
			*timeo = schedule_timeout(*timeo);
			skb = skb_dequeue(&sk->sk_receive_queue);
		}
		lock_sock(sk);
		if (skb != NULL)
			break;
		err = -EINVAL;
		if (sk->sk_state != TCP_LISTEN)
			break;
		err = sock_intr_errno(*timeo);
		if (signal_pending(current))
			break;
		err = -EAGAIN;
		if (!*timeo)
			break;
		prepare_to_wait(sk_sleep(sk), &wait, TASK_INTERRUPTIBLE);
	}
	finish_wait(sk_sleep(sk), &wait);

	return skb == NULL ? ERR_PTR(err) : skb;
}
