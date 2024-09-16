static inline int dn_check_state(struct sock *sk, struct sockaddr_dn *addr, int addrlen, long *timeo, int flags)
{
	struct dn_scp *scp = DN_SK(sk);

	switch (scp->state) {
	case DN_RUN:
		return 0;
	case DN_CR:
		return dn_confirm_accept(sk, timeo, sk->sk_allocation);
	case DN_CI:
	case DN_CC:
		return dn_wait_run(sk, timeo);
	case DN_O:
		return __dn_connect(sk, addr, addrlen, timeo, flags);
	}

	return -EINVAL;
}
