static int crypto_authenc_esn_verify(struct aead_request *req)
{
	struct crypto_aead *authenc_esn = crypto_aead_reqtfm(req);
	struct authenc_esn_request_ctx *areq_ctx = aead_request_ctx(req);
	u8 *ohash;
	u8 *ihash;
	unsigned int authsize;

	areq_ctx->complete = authenc_esn_verify_ahash_done;
	areq_ctx->update_complete = authenc_esn_verify_ahash_update_done;

	ohash = crypto_authenc_esn_ahash(req, CRYPTO_TFM_REQ_MAY_SLEEP);
	if (IS_ERR(ohash))
		return PTR_ERR(ohash);

	authsize = crypto_aead_authsize(authenc_esn);
	ihash = ohash + authsize;
	scatterwalk_map_and_copy(ihash, areq_ctx->sg, areq_ctx->cryptlen,
				 authsize, 0);
	return crypto_memneq(ihash, ohash, authsize) ? -EBADMSG : 0;
}
