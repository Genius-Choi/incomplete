nlmsvc_defer_lock_rqst(struct svc_rqst *rqstp, struct nlm_block *block)
{
	__be32 status = nlm_lck_denied_nolocks;

	block->b_flags |= B_QUEUED;

	nlmsvc_insert_block(block, NLM_TIMEOUT);

	block->b_cache_req = &rqstp->rq_chandle;
	if (rqstp->rq_chandle.defer) {
		block->b_deferred_req =
			rqstp->rq_chandle.defer(block->b_cache_req);
		if (block->b_deferred_req != NULL)
			status = nlm_drop_reply;
	}
	dprintk("lockd: nlmsvc_defer_lock_rqst block %p flags %d status %d\n",
		block, block->b_flags, ntohl(status));

	return status;
}
