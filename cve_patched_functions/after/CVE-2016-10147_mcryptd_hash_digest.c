static void mcryptd_hash_digest(struct crypto_async_request *req_async, int err)
{
	struct mcryptd_hash_ctx *ctx = crypto_tfm_ctx(req_async->tfm);
	struct crypto_ahash *child = ctx->child;
	struct ahash_request *req = ahash_request_cast(req_async);
	struct mcryptd_hash_request_ctx *rctx = ahash_request_ctx(req);
	struct ahash_request *desc = &rctx->areq;

	if (unlikely(err == -EINPROGRESS))
		goto out;

	ahash_request_set_tfm(desc, child);
	ahash_request_set_callback(desc, CRYPTO_TFM_REQ_MAY_SLEEP,
						rctx->complete, req_async);

	rctx->out = req->result;
	err = ahash_mcryptd_digest(desc);

out:
	local_bh_disable();
	rctx->complete(&req->base, err);
	local_bh_enable();
}
