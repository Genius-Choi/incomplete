void rds_ib_send_init_ring(struct rds_ib_connection *ic)
{
	struct rds_ib_send_work *send;
	u32 i;

	for (i = 0, send = ic->i_sends; i < ic->i_send_ring.w_nr; i++, send++) {
		struct ib_sge *sge;

		send->s_op = NULL;

		send->s_wr.wr_id = i;
		send->s_wr.sg_list = send->s_sge;
		send->s_wr.ex.imm_data = 0;

		sge = &send->s_sge[0];
		sge->addr = ic->i_send_hdrs_dma + (i * sizeof(struct rds_header));
		sge->length = sizeof(struct rds_header);
		sge->lkey = ic->i_mr->lkey;

		send->s_sge[1].lkey = ic->i_mr->lkey;
	}
}
