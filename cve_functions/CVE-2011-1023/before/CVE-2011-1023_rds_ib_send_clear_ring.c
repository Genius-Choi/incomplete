void rds_ib_send_clear_ring(struct rds_ib_connection *ic)
{
	struct rds_ib_send_work *send;
	u32 i;

	for (i = 0, send = ic->i_sends; i < ic->i_send_ring.w_nr; i++, send++) {
		if (send->s_op && send->s_wr.opcode != 0xdead)
			rds_ib_send_unmap_op(ic, send, IB_WC_WR_FLUSH_ERR);
	}
}
