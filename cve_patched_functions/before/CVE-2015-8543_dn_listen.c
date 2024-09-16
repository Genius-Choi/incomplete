static int dn_listen(struct socket *sock, int backlog)
{
	struct sock *sk = sock->sk;
	int err = -EINVAL;

	lock_sock(sk);

	if (sock_flag(sk, SOCK_ZAPPED))
		goto out;

	if ((DN_SK(sk)->state != DN_O) || (sk->sk_state == TCP_LISTEN))
		goto out;

	sk->sk_max_ack_backlog = backlog;
	sk->sk_ack_backlog     = 0;
	sk->sk_state           = TCP_LISTEN;
	err                 = 0;
	dn_rehash_sock(sk);

out:
	release_sock(sk);

	return err;
}
