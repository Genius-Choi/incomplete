void rds_ib_send_add_credits(struct rds_connection *conn, unsigned int credits)
{
	struct rds_ib_connection *ic = conn->c_transport_data;

	if (credits == 0)
		return;

	rdsdebug("rds_ib_send_add_credits(%u): current=%u%s\n",
			credits,
			IB_GET_SEND_CREDITS(atomic_read(&ic->i_credits)),
			test_bit(RDS_LL_SEND_FULL, &conn->c_flags) ? ", ll_send_full" : "");

	atomic_add(IB_SET_SEND_CREDITS(credits), &ic->i_credits);
	if (test_and_clear_bit(RDS_LL_SEND_FULL, &conn->c_flags))
		queue_delayed_work(rds_wq, &conn->c_send_w, 0);

	WARN_ON(IB_GET_SEND_CREDITS(credits) >= 16384);

	rds_ib_stats_inc(s_ib_rx_credit_updates);
}
