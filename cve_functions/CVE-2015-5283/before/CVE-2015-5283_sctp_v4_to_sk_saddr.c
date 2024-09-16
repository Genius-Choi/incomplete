static void sctp_v4_to_sk_saddr(union sctp_addr *addr, struct sock *sk)
{
	inet_sk(sk)->inet_rcv_saddr = addr->v4.sin_addr.s_addr;
}
