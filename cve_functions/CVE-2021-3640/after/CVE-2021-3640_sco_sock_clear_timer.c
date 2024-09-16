static void sco_sock_clear_timer(struct sock *sk)
{
	if (!sco_pi(sk)->conn)
		return;

	BT_DBG("sock %p state %d", sk, sk->sk_state);
	cancel_delayed_work(&sco_pi(sk)->conn->timeout_work);
}
