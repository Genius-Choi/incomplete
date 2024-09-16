static void tcp_v6_hash(struct sock *sk)
{
	if (sk->sk_state != TCP_CLOSE) {
		if (inet_csk(sk)->icsk_af_ops == &ipv6_mapped) {
			tcp_prot.hash(sk);
			return;
		}
		local_bh_disable();
		__inet6_hash(sk, NULL);
		local_bh_enable();
	}
}
