static void reject_rx_queue(struct sock *sk)
{
	struct sk_buff *buf;

	while ((buf = __skb_dequeue(&sk->sk_receive_queue)))
		tipc_reject_msg(buf, TIPC_ERR_NO_PORT);
}
