static int dn_shutdown(struct socket *sock, int how)
{
	struct sock *sk = sock->sk;
	struct dn_scp *scp = DN_SK(sk);
	int err = -ENOTCONN;

	lock_sock(sk);

	if (sock->state == SS_UNCONNECTED)
		goto out;

	err = 0;
	if (sock->state == SS_DISCONNECTING)
		goto out;

	err = -EINVAL;
	if (scp->state == DN_O)
		goto out;

	if (how != SHUT_RDWR)
		goto out;

	sk->sk_shutdown = SHUTDOWN_MASK;
	dn_destroy_sock(sk);
	err = 0;

out:
	release_sock(sk);

	return err;
}
