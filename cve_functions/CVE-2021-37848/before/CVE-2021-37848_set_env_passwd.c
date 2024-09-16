int set_env_passwd(unsigned char* passwd, size_t length)
{
	struct digest *d = NULL;
	unsigned char *passwd_sum;
	int ret, hash_len;

	if (IS_ENABLED(CONFIG_PASSWD_CRYPTO_PBKDF2)) {
		hash_len = PBKDF2_LENGTH;
	} else {
		d = digest_alloc(PASSWD_SUM);
		if (!d)
			return -EINVAL;

		hash_len = digest_length(d);
	}

	passwd_sum = calloc(hash_len, sizeof(unsigned char));
	if (!passwd_sum)
		return -ENOMEM;

	if (IS_ENABLED(CONFIG_PASSWD_CRYPTO_PBKDF2)) {
		char *key = passwd_sum + PBKDF2_SALT_LEN;
		char *salt = passwd_sum;
		int keylen = PBKDF2_LENGTH - PBKDF2_SALT_LEN;

		ret = get_crypto_bytes(passwd_sum, PBKDF2_SALT_LEN);
		if (ret) {
			pr_err("Can't get random numbers\n");
			return ret;
		}

		ret = pkcs5_pbkdf2_hmac_sha1(passwd, length, salt,
				PBKDF2_SALT_LEN, PBKDF2_COUNT, keylen, key);
	} else {
		ret = digest_digest(d, passwd, length, passwd_sum);
	}
	if (ret)
		goto err;

	ret = write_env_passwd(passwd_sum, hash_len);

err:
	digest_free(d);
	free(passwd_sum);

	return ret;
}
