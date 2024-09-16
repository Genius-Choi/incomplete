static int tcp_v4_rtx_synack(struct sock *sk, struct request_sock *req,
			      struct request_values *rvp)
{
	TCP_INC_STATS_BH(sock_net(sk), TCP_MIB_RETRANSSEGS);
	return tcp_v4_send_synack(sk, NULL, req, rvp);
}
