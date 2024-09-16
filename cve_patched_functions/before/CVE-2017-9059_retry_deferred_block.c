retry_deferred_block(struct nlm_block *block)
{
	if (!(block->b_flags & B_GOT_CALLBACK))
		block->b_flags |= B_TIMED_OUT;
	nlmsvc_insert_block(block, NLM_TIMEOUT);
	dprintk("revisit block %p flags %d\n",	block, block->b_flags);
	if (block->b_deferred_req) {
		block->b_deferred_req->revisit(block->b_deferred_req, 0);
		block->b_deferred_req = NULL;
	}
}
