static void sd_unprep_fn(struct request_queue *q, struct request *rq)
{
	if (rq->cmd_flags & REQ_DISCARD) {
		free_page((unsigned long)rq->buffer);
		rq->buffer = NULL;
	}
}
