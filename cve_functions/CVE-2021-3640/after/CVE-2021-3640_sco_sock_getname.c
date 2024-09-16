static int sco_sock_getname(struct socket *sock, struct sockaddr *addr,
			    int peer)
{
	struct sockaddr_sco *sa = (struct sockaddr_sco *) addr;
	struct sock *sk = sock->sk;

	BT_DBG("sock %p, sk %p", sock, sk);

	addr->sa_family = AF_BLUETOOTH;

	if (peer)
		bacpy(&sa->sco_bdaddr, &sco_pi(sk)->dst);
	else
		bacpy(&sa->sco_bdaddr, &sco_pi(sk)->src);

	return sizeof(struct sockaddr_sco);
}
