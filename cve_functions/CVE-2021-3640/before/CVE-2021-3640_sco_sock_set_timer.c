static void sco_sock_set_timer(struct sock *sk, long timeout)
{
	if (!sco_pi(sk)->conn)
		return;

	BT_DBG("sock %p state %d timeout %ld", sk, sk->sk_state, timeout);
	cancel_delayed_work(&sco_pi(sk)->conn->timeout_work);
	schedule_delayed_work(&sco_pi(sk)->conn->timeout_work, timeout);
}
