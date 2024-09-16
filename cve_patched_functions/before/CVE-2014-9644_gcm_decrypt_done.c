static void gcm_decrypt_done(struct crypto_async_request *areq, int err)
{
	struct aead_request *req = areq->data;
	struct crypto_gcm_req_priv_ctx *pctx = crypto_gcm_reqctx(req);

	if (!err)
		err = crypto_gcm_verify(req, pctx);

	aead_request_complete(req, err);
}
