static int send_packet(struct kiocb *iocb, struct socket *sock,
		       struct msghdr *m, size_t total_len)
{
	struct sock *sk = sock->sk;
	struct tipc_port *tport = tipc_sk_port(sk);
	struct sockaddr_tipc *dest = (struct sockaddr_tipc *)m->msg_name;
	long timeout_val;
	int res;

	/* Handle implied connection establishment */
	if (unlikely(dest))
		return send_msg(iocb, sock, m, total_len);

	if (total_len > TIPC_MAX_USER_MSG_SIZE)
		return -EMSGSIZE;

	if (iocb)
		lock_sock(sk);

	timeout_val = sock_sndtimeo(sk, m->msg_flags & MSG_DONTWAIT);

	do {
		if (unlikely(sock->state != SS_CONNECTED)) {
			if (sock->state == SS_DISCONNECTING)
				res = -EPIPE;
			else
				res = -ENOTCONN;
			break;
		}

		res = tipc_send(tport->ref, m->msg_iov, total_len);
		if (likely(res != -ELINKCONG))
			break;
		if (timeout_val <= 0L) {
			res = timeout_val ? timeout_val : -EWOULDBLOCK;
			break;
		}
		release_sock(sk);
		timeout_val = wait_event_interruptible_timeout(*sk_sleep(sk),
			(!tport->congested || !tport->connected), timeout_val);
		lock_sock(sk);
	} while (1);

	if (iocb)
		release_sock(sk);
	return res;
}
