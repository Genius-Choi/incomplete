int sk_wait_data(struct sock *sk, long *timeo, const struct sk_buff *skb)
{
	int rc;
	DEFINE_WAIT(wait);

	prepare_to_wait(sk_sleep(sk), &wait, TASK_INTERRUPTIBLE);
	sk_set_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	rc = sk_wait_event(sk, timeo, skb_peek_tail(&sk->sk_receive_queue) != skb);
	sk_clear_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	finish_wait(sk_sleep(sk), &wait);
	return rc;
}
