static void srpt_rdma_read_done(struct ib_cq *cq, struct ib_wc *wc)
{
	struct srpt_rdma_ch *ch = cq->cq_context;
	struct srpt_send_ioctx *ioctx =
		container_of(wc->wr_cqe, struct srpt_send_ioctx, rdma_cqe);

	WARN_ON(ioctx->n_rdma <= 0);
	atomic_add(ioctx->n_rdma, &ch->sq_wr_avail);

	if (unlikely(wc->status != IB_WC_SUCCESS)) {
		pr_info("RDMA_READ for ioctx 0x%p failed with status %d\n",
			ioctx, wc->status);
		srpt_abort_cmd(ioctx);
		return;
	}

	if (srpt_test_and_set_cmd_state(ioctx, SRPT_STATE_NEED_DATA,
					SRPT_STATE_DATA_IN))
		target_execute_cmd(&ioctx->cmd);
	else
		pr_err("%s[%d]: wrong state = %d\n", __func__,
		       __LINE__, srpt_get_cmd_state(ioctx));
}
