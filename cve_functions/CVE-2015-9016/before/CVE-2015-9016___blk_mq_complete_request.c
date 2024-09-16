void __blk_mq_complete_request(struct request *rq)
{
	struct request_queue *q = rq->q;

	if (!q->softirq_done_fn)
		blk_mq_end_request(rq, rq->errors);
	else
		blk_mq_ipi_complete_request(rq);
}
