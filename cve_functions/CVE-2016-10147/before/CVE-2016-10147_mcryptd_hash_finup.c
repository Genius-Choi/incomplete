static void mcryptd_hash_finup(struct crypto_async_request *req_async, int err)
{
	struct ahash_request *req = ahash_request_cast(req_async);
	struct mcryptd_hash_request_ctx *rctx = ahash_request_ctx(req);

	if (unlikely(err == -EINPROGRESS))
		goto out;
	rctx->out = req->result;
	err = ahash_mcryptd_finup(&rctx->areq);

	if (err) {
		req->base.complete = rctx->complete;
		goto out;
	}

	return;
out:
	local_bh_disable();
	rctx->complete(&req->base, err);
	local_bh_enable();
}
