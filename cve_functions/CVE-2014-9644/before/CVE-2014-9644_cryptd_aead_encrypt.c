static void cryptd_aead_encrypt(struct crypto_async_request *areq, int err)
{
	struct cryptd_aead_ctx *ctx = crypto_tfm_ctx(areq->tfm);
	struct crypto_aead *child = ctx->child;
	struct aead_request *req;

	req = container_of(areq, struct aead_request, base);
	cryptd_aead_crypt(req, child, err, crypto_aead_crt(child)->encrypt);
}
