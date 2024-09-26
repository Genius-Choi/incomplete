static int unix_release(struct socket *sock)
{
	struct sock *sk = sock->sk;

	if (!sk)
		return 0;

	sock->sk = NULL;

	return unix_release_sock(sk, 0);
}
