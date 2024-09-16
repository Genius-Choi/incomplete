static void sco_sock_timeout(struct work_struct *work)
{
	struct sco_conn *conn = container_of(work, struct sco_conn,
					     timeout_work.work);
	struct sock *sk;

	sco_conn_lock(conn);
	sk = conn->sk;
	if (sk)
		sock_hold(sk);
	sco_conn_unlock(conn);

	if (!sk)
		return;

	BT_DBG("sock %p state %d", sk, sk->sk_state);

	lock_sock(sk);
	sk->sk_err = ETIMEDOUT;
	sk->sk_state_change(sk);
	release_sock(sk);
	sock_put(sk);
}
