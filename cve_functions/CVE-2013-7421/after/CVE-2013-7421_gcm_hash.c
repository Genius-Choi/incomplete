static int gcm_hash(struct aead_request *req,
		    struct crypto_gcm_req_priv_ctx *pctx)
{
	struct ahash_request *ahreq = &pctx->u.ahreq;
	struct crypto_gcm_ghash_ctx *gctx = &pctx->ghash_ctx;
	struct crypto_gcm_ctx *ctx = crypto_tfm_ctx(req->base.tfm);
	unsigned int remain;
	crypto_completion_t compl;
	int err;

	ahash_request_set_tfm(ahreq, ctx->ghash);

	ahash_request_set_callback(ahreq, aead_request_flags(req),
				   gcm_hash_init_done, req);
	err = crypto_ahash_init(ahreq);
	if (err)
		return err;
	remain = gcm_remain(req->assoclen);
	compl = remain ? gcm_hash_assoc_done : gcm_hash_assoc_remain_done;
	err = gcm_hash_update(req, pctx, compl, req->assoc, req->assoclen);
	if (err)
		return err;
	if (remain) {
		err = gcm_hash_remain(req, pctx, remain,
				      gcm_hash_assoc_remain_done);
		if (err)
			return err;
	}
	remain = gcm_remain(gctx->cryptlen);
	compl = remain ? gcm_hash_crypt_done : gcm_hash_crypt_remain_done;
	err = gcm_hash_update(req, pctx, compl, gctx->src, gctx->cryptlen);
	if (err)
		return err;
	if (remain) {
		err = gcm_hash_remain(req, pctx, remain,
				      gcm_hash_crypt_remain_done);
		if (err)
			return err;
	}
	err = gcm_hash_len(req, pctx);
	if (err)
		return err;
	err = gcm_hash_final(req, pctx);
	if (err)
		return err;

	return 0;
}
