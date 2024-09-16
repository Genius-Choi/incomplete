static blk_status_t pf_queue_rq(struct blk_mq_hw_ctx *hctx,
				const struct blk_mq_queue_data *bd)
{
	struct pf_unit *pf = hctx->queue->queuedata;

	spin_lock_irq(&pf_spin_lock);
	list_add_tail(&bd->rq->queuelist, &pf->rq_list);
	pf_request();
	spin_unlock_irq(&pf_spin_lock);

	return BLK_STS_OK;
}
