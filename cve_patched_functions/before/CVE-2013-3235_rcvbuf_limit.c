static unsigned int rcvbuf_limit(struct sock *sk, struct sk_buff *buf)
{
	struct tipc_msg *msg = buf_msg(buf);
	unsigned int limit;

	if (msg_connected(msg))
		limit = CONN_OVERLOAD_LIMIT;
	else
		limit = sk->sk_rcvbuf << (msg_importance(msg) + 5);
	return limit;
}
