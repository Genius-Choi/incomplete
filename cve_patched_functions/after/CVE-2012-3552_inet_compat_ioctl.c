int inet_compat_ioctl(struct socket *sock, unsigned int cmd, unsigned long arg)
{
	struct sock *sk = sock->sk;
	int err = -ENOIOCTLCMD;

	if (sk->sk_prot->compat_ioctl)
		err = sk->sk_prot->compat_ioctl(sk, cmd, arg);

	return err;
}
