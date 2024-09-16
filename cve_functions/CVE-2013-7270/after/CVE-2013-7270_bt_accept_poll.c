static inline unsigned int bt_accept_poll(struct sock *parent)
{
	struct list_head *p, *n;
	struct sock *sk;

	list_for_each_safe(p, n, &bt_sk(parent)->accept_q) {
		sk = (struct sock *) list_entry(p, struct bt_sock, accept_q);
		if (sk->sk_state == BT_CONNECTED ||
		    (test_bit(BT_SK_DEFER_SETUP, &bt_sk(parent)->flags) &&
		     sk->sk_state == BT_CONNECT2))
			return POLLIN | POLLRDNORM;
	}

	return 0;
}
