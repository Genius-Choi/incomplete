static void rds_ib_send_unmap_data(struct rds_ib_connection *ic,
				   struct rm_data_op *op,
				   int wc_status)
{
	if (op->op_nents)
		ib_dma_unmap_sg(ic->i_cm_id->device,
				op->op_sg, op->op_nents,
				DMA_TO_DEVICE);
}
