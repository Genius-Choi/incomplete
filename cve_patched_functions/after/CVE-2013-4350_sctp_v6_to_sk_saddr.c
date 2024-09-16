static void sctp_v6_to_sk_saddr(union sctp_addr *addr, struct sock *sk)
{
	if (addr->sa.sa_family == AF_INET && sctp_sk(sk)->v4mapped) {
		inet6_sk(sk)->rcv_saddr.s6_addr32[0] = 0;
		inet6_sk(sk)->rcv_saddr.s6_addr32[1] = 0;
		inet6_sk(sk)->rcv_saddr.s6_addr32[2] = htonl(0x0000ffff);
		inet6_sk(sk)->rcv_saddr.s6_addr32[3] =
			addr->v4.sin_addr.s_addr;
	} else {
		inet6_sk(sk)->rcv_saddr = addr->v6.sin6_addr;
	}
}
