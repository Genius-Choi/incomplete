static void srpt_unmap_sg_to_ib_sge(struct srpt_rdma_ch *ch,
				    struct srpt_send_ioctx *ioctx)
{
	struct scatterlist *sg;
	enum dma_data_direction dir;

	BUG_ON(!ch);
	BUG_ON(!ioctx);
	BUG_ON(ioctx->n_rdma && !ioctx->rdma_wrs);

	while (ioctx->n_rdma)
		kfree(ioctx->rdma_wrs[--ioctx->n_rdma].wr.sg_list);

	kfree(ioctx->rdma_wrs);
	ioctx->rdma_wrs = NULL;

	if (ioctx->mapped_sg_count) {
		sg = ioctx->sg;
		WARN_ON(!sg);
		dir = ioctx->cmd.data_direction;
		BUG_ON(dir == DMA_NONE);
		ib_dma_unmap_sg(ch->sport->sdev->device, sg, ioctx->sg_cnt,
				opposite_dma_dir(dir));
		ioctx->mapped_sg_count = 0;
	}
}
