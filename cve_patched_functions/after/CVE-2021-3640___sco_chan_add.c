static void __sco_chan_add(struct sco_conn *conn, struct sock *sk,
			   struct sock *parent)
{
	BT_DBG("conn %p", conn);

	sco_pi(sk)->conn = conn;
	conn->sk = sk;

	INIT_DELAYED_WORK(&conn->timeout_work, sco_sock_timeout);

	if (parent)
		bt_accept_enqueue(parent, sk, true);
}
