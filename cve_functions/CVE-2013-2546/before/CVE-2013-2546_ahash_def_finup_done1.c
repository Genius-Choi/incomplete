static void ahash_def_finup_done1(struct crypto_async_request *req, int err)
{
	struct ahash_request *areq = req->data;
	struct ahash_request_priv *priv = areq->priv;
	crypto_completion_t complete = priv->complete;
	void *data = priv->data;

	err = ahash_def_finup_finish1(areq, err);

	complete(data, err);
}
