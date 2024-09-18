static inline struct l2tp_session *pppol2tp_sock_to_session(struct sock *sk)
{
	struct l2tp_session *session;

	if (sk == NULL)
		return NULL;

	sock_hold(sk);
	session = (struct l2tp_session *)(sk->sk_user_data);
	if (session == NULL) {
		sock_put(sk);
		goto out;
	}

	BUG_ON(session->magic != L2TP_SESSION_MAGIC);

out:
	return session;
}
