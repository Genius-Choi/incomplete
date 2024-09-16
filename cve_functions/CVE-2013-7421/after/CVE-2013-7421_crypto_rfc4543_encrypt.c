static int crypto_rfc4543_encrypt(struct aead_request *req)
{
	struct crypto_aead *aead = crypto_aead_reqtfm(req);
	struct crypto_rfc4543_req_ctx *rctx = crypto_rfc4543_reqctx(req);
	struct aead_request *subreq;
	int err;

	if (req->src != req->dst) {
		err = crypto_rfc4543_copy_src_to_dst(req, true);
		if (err)
			return err;
	}

	subreq = crypto_rfc4543_crypt(req, true);
	err = crypto_aead_encrypt(subreq);
	if (err)
		return err;

	scatterwalk_map_and_copy(rctx->auth_tag, req->dst, req->cryptlen,
				 crypto_aead_authsize(aead), 1);

	return 0;
}
