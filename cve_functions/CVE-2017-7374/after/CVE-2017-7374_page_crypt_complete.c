static void page_crypt_complete(struct crypto_async_request *req, int res)
{
	struct fscrypt_completion_result *ecr = req->data;

	if (res == -EINPROGRESS)
		return;
	ecr->res = res;
	complete(&ecr->completion);
}
