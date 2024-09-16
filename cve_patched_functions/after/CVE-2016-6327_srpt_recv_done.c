static void srpt_recv_done(struct ib_cq *cq, struct ib_wc *wc)
{
	struct srpt_rdma_ch *ch = cq->cq_context;
	struct srpt_recv_ioctx *ioctx =
		container_of(wc->wr_cqe, struct srpt_recv_ioctx, ioctx.cqe);

	if (wc->status == IB_WC_SUCCESS) {
		int req_lim;

		req_lim = atomic_dec_return(&ch->req_lim);
		if (unlikely(req_lim < 0))
			pr_err("req_lim = %d < 0\n", req_lim);
		srpt_handle_new_iu(ch, ioctx, NULL);
	} else {
		pr_info("receiving failed for ioctx %p with status %d\n",
			ioctx, wc->status);
	}
}
