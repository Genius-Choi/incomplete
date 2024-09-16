static int dccp_rcv_close(struct sock *sk, struct sk_buff *skb)
{
	int queued = 0;

	switch (sk->sk_state) {
	/*
	 * We ignore Close when received in one of the following states:
	 *  - CLOSED		(may be a late or duplicate packet)
	 *  - PASSIVE_CLOSEREQ	(the peer has sent a CloseReq earlier)
	 *  - RESPOND		(already handled by dccp_check_req)
	 */
	case DCCP_CLOSING:
		/*
		 * Simultaneous-close: receiving a Close after sending one. This
		 * can happen if both client and server perform active-close and
		 * will result in an endless ping-pong of crossing and retrans-
		 * mitted Close packets, which only terminates when one of the
		 * nodes times out (min. 64 seconds). Quicker convergence can be
		 * achieved when one of the nodes acts as tie-breaker.
		 * This is ok as both ends are done with data transfer and each
		 * end is just waiting for the other to acknowledge termination.
		 */
		if (dccp_sk(sk)->dccps_role != DCCP_ROLE_CLIENT)
			break;
		/* fall through */
	case DCCP_REQUESTING:
	case DCCP_ACTIVE_CLOSEREQ:
		dccp_send_reset(sk, DCCP_RESET_CODE_CLOSED);
		dccp_done(sk);
		break;
	case DCCP_OPEN:
	case DCCP_PARTOPEN:
		/* Give waiting application a chance to read pending data */
		queued = 1;
		dccp_fin(sk, skb);
		dccp_set_state(sk, DCCP_PASSIVE_CLOSE);
		/* fall through */
	case DCCP_PASSIVE_CLOSE:
		/*
		 * Retransmitted Close: we have already enqueued the first one.
		 */
		sk_wake_async(sk, SOCK_WAKE_WAITD, POLL_HUP);
	}
	return queued;
}
