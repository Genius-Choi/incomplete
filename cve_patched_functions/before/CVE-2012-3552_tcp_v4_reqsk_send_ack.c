static void tcp_v4_reqsk_send_ack(struct sock *sk, struct sk_buff *skb,
				  struct request_sock *req)
{
	tcp_v4_send_ack(skb, tcp_rsk(req)->snt_isn + 1,
			tcp_rsk(req)->rcv_isn + 1, req->rcv_wnd,
			req->ts_recent,
			0,
			tcp_v4_md5_do_lookup(sk, ip_hdr(skb)->daddr),
			inet_rsk(req)->no_srccheck ? IP_REPLY_ARG_NOSRCCHECK : 0);
}
