static int dn_getname(struct socket *sock, struct sockaddr *uaddr,int *uaddr_len,int peer)
{
	struct sockaddr_dn *sa = (struct sockaddr_dn *)uaddr;
	struct sock *sk = sock->sk;
	struct dn_scp *scp = DN_SK(sk);

	*uaddr_len = sizeof(struct sockaddr_dn);

	lock_sock(sk);

	if (peer) {
		if ((sock->state != SS_CONNECTED &&
		     sock->state != SS_CONNECTING) &&
		    scp->accept_mode == ACC_IMMED) {
			release_sock(sk);
			return -ENOTCONN;
		}

		memcpy(sa, &scp->peer, sizeof(struct sockaddr_dn));
	} else {
		memcpy(sa, &scp->addr, sizeof(struct sockaddr_dn));
	}

	release_sock(sk);

	return 0;
}
