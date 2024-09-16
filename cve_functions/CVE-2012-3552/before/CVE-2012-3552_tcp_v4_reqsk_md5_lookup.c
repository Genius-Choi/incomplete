static struct tcp_md5sig_key *tcp_v4_reqsk_md5_lookup(struct sock *sk,
						      struct request_sock *req)
{
	return tcp_v4_md5_do_lookup(sk, inet_rsk(req)->rmt_addr);
}
