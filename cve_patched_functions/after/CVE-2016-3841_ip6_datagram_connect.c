int ip6_datagram_connect(struct sock *sk, struct sockaddr *uaddr, int addr_len)
{
	int res;

	lock_sock(sk);
	res = __ip6_datagram_connect(sk, uaddr, addr_len);
	release_sock(sk);
	return res;
}
