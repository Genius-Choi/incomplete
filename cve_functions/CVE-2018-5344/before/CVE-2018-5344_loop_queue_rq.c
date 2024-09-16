static blk_status_t loop_queue_rq(struct blk_mq_hw_ctx *hctx,
		const struct blk_mq_queue_data *bd)
{
	struct loop_cmd *cmd = blk_mq_rq_to_pdu(bd->rq);
	struct loop_device *lo = cmd->rq->q->queuedata;

	blk_mq_start_request(bd->rq);

	if (lo->lo_state != Lo_bound)
		return BLK_STS_IOERR;

	switch (req_op(cmd->rq)) {
	case REQ_OP_FLUSH:
	case REQ_OP_DISCARD:
	case REQ_OP_WRITE_ZEROES:
		cmd->use_aio = false;
		break;
	default:
		cmd->use_aio = lo->use_dio;
		break;
	}

	/* always use the first bio's css */
#ifdef CONFIG_BLK_CGROUP
	if (cmd->use_aio && cmd->rq->bio && cmd->rq->bio->bi_css) {
		cmd->css = cmd->rq->bio->bi_css;
		css_get(cmd->css);
	} else
#endif
		cmd->css = NULL;
	kthread_queue_work(&lo->worker, &cmd->work);

	return BLK_STS_OK;
}
