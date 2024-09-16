static bool tcp_tsopt_ecr_before(const struct tcp_sock *tp, u32 when)
{
	return tp->rx_opt.saw_tstamp && tp->rx_opt.rcv_tsecr &&
	       before(tp->rx_opt.rcv_tsecr, when);
}
