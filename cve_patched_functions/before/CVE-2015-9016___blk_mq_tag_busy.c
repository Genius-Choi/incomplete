bool __blk_mq_tag_busy(struct blk_mq_hw_ctx *hctx)
{
	if (!test_bit(BLK_MQ_S_TAG_ACTIVE, &hctx->state) &&
	    !test_and_set_bit(BLK_MQ_S_TAG_ACTIVE, &hctx->state))
		atomic_inc(&hctx->tags->active_queues);

	return true;
}
