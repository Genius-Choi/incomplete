static int dn_connect(struct socket *sock, struct sockaddr *uaddr, int addrlen, int flags)
{
	struct sockaddr_dn *addr = (struct sockaddr_dn *)uaddr;
	struct sock *sk = sock->sk;
	int err;
	long timeo = sock_sndtimeo(sk, flags & O_NONBLOCK);

	lock_sock(sk);
	err = __dn_connect(sk, addr, addrlen, &timeo, 0);
	release_sock(sk);

	return err;
}
