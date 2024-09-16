int vcc_release(struct socket *sock)
{
	struct sock *sk = sock->sk;

	if (sk) {
		lock_sock(sk);
		vcc_destroy_socket(sock->sk);
		release_sock(sk);
		sock_put(sk);
	}

	return 0;
}
