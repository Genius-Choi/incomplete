int crypto_ahash_digest(struct ahash_request *req)
{
	return crypto_ahash_op(req, crypto_ahash_reqtfm(req)->digest);
}
