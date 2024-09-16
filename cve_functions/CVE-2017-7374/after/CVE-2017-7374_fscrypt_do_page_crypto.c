int fscrypt_do_page_crypto(const struct inode *inode, fscrypt_direction_t rw,
			   u64 lblk_num, struct page *src_page,
			   struct page *dest_page, unsigned int len,
			   unsigned int offs, gfp_t gfp_flags)
{
	struct {
		__le64 index;
		u8 padding[FS_XTS_TWEAK_SIZE - sizeof(__le64)];
	} xts_tweak;
	struct skcipher_request *req = NULL;
	DECLARE_FS_COMPLETION_RESULT(ecr);
	struct scatterlist dst, src;
	struct fscrypt_info *ci = inode->i_crypt_info;
	struct crypto_skcipher *tfm = ci->ci_ctfm;
	int res = 0;

	BUG_ON(len == 0);

	req = skcipher_request_alloc(tfm, gfp_flags);
	if (!req) {
		printk_ratelimited(KERN_ERR
				"%s: crypto_request_alloc() failed\n",
				__func__);
		return -ENOMEM;
	}

	skcipher_request_set_callback(
		req, CRYPTO_TFM_REQ_MAY_BACKLOG | CRYPTO_TFM_REQ_MAY_SLEEP,
		page_crypt_complete, &ecr);

	BUILD_BUG_ON(sizeof(xts_tweak) != FS_XTS_TWEAK_SIZE);
	xts_tweak.index = cpu_to_le64(lblk_num);
	memset(xts_tweak.padding, 0, sizeof(xts_tweak.padding));

	sg_init_table(&dst, 1);
	sg_set_page(&dst, dest_page, len, offs);
	sg_init_table(&src, 1);
	sg_set_page(&src, src_page, len, offs);
	skcipher_request_set_crypt(req, &src, &dst, len, &xts_tweak);
	if (rw == FS_DECRYPT)
		res = crypto_skcipher_decrypt(req);
	else
		res = crypto_skcipher_encrypt(req);
	if (res == -EINPROGRESS || res == -EBUSY) {
		BUG_ON(req->base.data != &ecr);
		wait_for_completion(&ecr.completion);
		res = ecr.res;
	}
	skcipher_request_free(req);
	if (res) {
		printk_ratelimited(KERN_ERR
			"%s: crypto_skcipher_encrypt() returned %d\n",
			__func__, res);
		return res;
	}
	return 0;
}
