int blk_mq_update_nr_requests(struct request_queue *q, unsigned int nr)
{
	struct blk_mq_tag_set *set = q->tag_set;
	struct blk_mq_hw_ctx *hctx;
	int i, ret;

	if (!set || nr > set->queue_depth)
		return -EINVAL;

	ret = 0;
	queue_for_each_hw_ctx(q, hctx, i) {
		ret = blk_mq_tag_update_depth(hctx->tags, nr);
		if (ret)
			break;
	}

	if (!ret)
		q->nr_requests = nr;

	return ret;
}
