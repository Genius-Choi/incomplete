static int srpt_post_send(struct srpt_rdma_ch *ch,
			  struct srpt_send_ioctx *ioctx, int len)
{
	struct ib_sge list;
	struct ib_send_wr wr, *bad_wr;
	struct srpt_device *sdev = ch->sport->sdev;
	int ret;

	atomic_inc(&ch->req_lim);

	ret = -ENOMEM;
	if (unlikely(atomic_dec_return(&ch->sq_wr_avail) < 0)) {
		pr_warn("IB send queue full (needed 1)\n");
		goto out;
	}

	ib_dma_sync_single_for_device(sdev->device, ioctx->ioctx.dma, len,
				      DMA_TO_DEVICE);

	list.addr = ioctx->ioctx.dma;
	list.length = len;
	list.lkey = sdev->pd->local_dma_lkey;

	ioctx->ioctx.cqe.done = srpt_send_done;
	wr.next = NULL;
	wr.wr_cqe = &ioctx->ioctx.cqe;
	wr.sg_list = &list;
	wr.num_sge = 1;
	wr.opcode = IB_WR_SEND;
	wr.send_flags = IB_SEND_SIGNALED;

	ret = ib_post_send(ch->qp, &wr, &bad_wr);

out:
	if (ret < 0) {
		atomic_inc(&ch->sq_wr_avail);
		atomic_dec(&ch->req_lim);
	}
	return ret;
}
