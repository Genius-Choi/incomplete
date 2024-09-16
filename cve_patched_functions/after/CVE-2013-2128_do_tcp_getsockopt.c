static int do_tcp_getsockopt(struct sock *sk, int level,
		int optname, char __user *optval, int __user *optlen)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct tcp_sock *tp = tcp_sk(sk);
	int val, len;

	if (get_user(len, optlen))
		return -EFAULT;

	len = min_t(unsigned int, len, sizeof(int));

	if (len < 0)
		return -EINVAL;

	switch (optname) {
	case TCP_MAXSEG:
		val = tp->mss_cache;
		if (!val && ((1 << sk->sk_state) & (TCPF_CLOSE | TCPF_LISTEN)))
			val = tp->rx_opt.user_mss;
		break;
	case TCP_NODELAY:
		val = !!(tp->nonagle&TCP_NAGLE_OFF);
		break;
	case TCP_CORK:
		val = !!(tp->nonagle&TCP_NAGLE_CORK);
		break;
	case TCP_KEEPIDLE:
		val = keepalive_time_when(tp) / HZ;
		break;
	case TCP_KEEPINTVL:
		val = keepalive_intvl_when(tp) / HZ;
		break;
	case TCP_KEEPCNT:
		val = keepalive_probes(tp);
		break;
	case TCP_SYNCNT:
		val = icsk->icsk_syn_retries ? : sysctl_tcp_syn_retries;
		break;
	case TCP_LINGER2:
		val = tp->linger2;
		if (val >= 0)
			val = (val ? : sysctl_tcp_fin_timeout) / HZ;
		break;
	case TCP_DEFER_ACCEPT:
		val = retrans_to_secs(icsk->icsk_accept_queue.rskq_defer_accept,
				      TCP_TIMEOUT_INIT / HZ, TCP_RTO_MAX / HZ);
		break;
	case TCP_WINDOW_CLAMP:
		val = tp->window_clamp;
		break;
	case TCP_INFO: {
		struct tcp_info info;

		if (get_user(len, optlen))
			return -EFAULT;

		tcp_get_info(sk, &info);

		len = min_t(unsigned int, len, sizeof(info));
		if (put_user(len, optlen))
			return -EFAULT;
		if (copy_to_user(optval, &info, len))
			return -EFAULT;
		return 0;
	}
	case TCP_QUICKACK:
		val = !icsk->icsk_ack.pingpong;
		break;

	case TCP_CONGESTION:
		if (get_user(len, optlen))
			return -EFAULT;
		len = min_t(unsigned int, len, TCP_CA_NAME_MAX);
		if (put_user(len, optlen))
			return -EFAULT;
		if (copy_to_user(optval, icsk->icsk_ca_ops->name, len))
			return -EFAULT;
		return 0;

	case TCP_COOKIE_TRANSACTIONS: {
		struct tcp_cookie_transactions ctd;
		struct tcp_cookie_values *cvp = tp->cookie_values;

		if (get_user(len, optlen))
			return -EFAULT;
		if (len < sizeof(ctd))
			return -EINVAL;

		memset(&ctd, 0, sizeof(ctd));
		ctd.tcpct_flags = (tp->rx_opt.cookie_in_always ?
				   TCP_COOKIE_IN_ALWAYS : 0)
				| (tp->rx_opt.cookie_out_never ?
				   TCP_COOKIE_OUT_NEVER : 0);

		if (cvp != NULL) {
			ctd.tcpct_flags |= (cvp->s_data_in ?
					    TCP_S_DATA_IN : 0)
					 | (cvp->s_data_out ?
					    TCP_S_DATA_OUT : 0);

			ctd.tcpct_cookie_desired = cvp->cookie_desired;
			ctd.tcpct_s_data_desired = cvp->s_data_desired;

			memcpy(&ctd.tcpct_value[0], &cvp->cookie_pair[0],
			       cvp->cookie_pair_size);
			ctd.tcpct_used = cvp->cookie_pair_size;
		}

		if (put_user(sizeof(ctd), optlen))
			return -EFAULT;
		if (copy_to_user(optval, &ctd, sizeof(ctd)))
			return -EFAULT;
		return 0;
	}
	default:
		return -ENOPROTOOPT;
	}

	if (put_user(len, optlen))
		return -EFAULT;
	if (copy_to_user(optval, &val, len))
		return -EFAULT;
	return 0;
}
