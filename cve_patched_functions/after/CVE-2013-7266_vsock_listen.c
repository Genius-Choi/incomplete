static int vsock_listen(struct socket *sock, int backlog)
{
	int err;
	struct sock *sk;
	struct vsock_sock *vsk;

	sk = sock->sk;

	lock_sock(sk);

	if (sock->type != SOCK_STREAM) {
		err = -EOPNOTSUPP;
		goto out;
	}

	if (sock->state != SS_UNCONNECTED) {
		err = -EINVAL;
		goto out;
	}

	vsk = vsock_sk(sk);

	if (!vsock_addr_bound(&vsk->local_addr)) {
		err = -EINVAL;
		goto out;
	}

	sk->sk_max_ack_backlog = backlog;
	sk->sk_state = SS_LISTEN;

	err = 0;

out:
	release_sock(sk);
	return err;
}
