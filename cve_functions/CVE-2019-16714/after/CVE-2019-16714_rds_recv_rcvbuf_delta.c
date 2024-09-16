static void rds_recv_rcvbuf_delta(struct rds_sock *rs, struct sock *sk,
				  struct rds_cong_map *map,
				  int delta, __be16 port)
{
	int now_congested;

	if (delta == 0)
		return;

	rs->rs_rcv_bytes += delta;
	if (delta > 0)
		rds_stats_add(s_recv_bytes_added_to_socket, delta);
	else
		rds_stats_add(s_recv_bytes_removed_from_socket, -delta);

	/* loop transport doesn't send/recv congestion updates */
	if (rs->rs_transport->t_type == RDS_TRANS_LOOP)
		return;

	now_congested = rs->rs_rcv_bytes > rds_sk_rcvbuf(rs);

	rdsdebug("rs %p (%pI6c:%u) recv bytes %d buf %d "
	  "now_cong %d delta %d\n",
	  rs, &rs->rs_bound_addr,
	  ntohs(rs->rs_bound_port), rs->rs_rcv_bytes,
	  rds_sk_rcvbuf(rs), now_congested, delta);

	/* wasn't -> am congested */
	if (!rs->rs_congested && now_congested) {
		rs->rs_congested = 1;
		rds_cong_set_bit(map, port);
		rds_cong_queue_updates(map);
	}
	/* was -> aren't congested */
	/* Require more free space before reporting uncongested to prevent
	   bouncing cong/uncong state too often */
	else if (rs->rs_congested && (rs->rs_rcv_bytes < (rds_sk_rcvbuf(rs)/2))) {
		rs->rs_congested = 0;
		rds_cong_clear_bit(map, port);
		rds_cong_queue_updates(map);
	}

	/* do nothing if no change in cong state */
}
