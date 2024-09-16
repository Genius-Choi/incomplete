kex_derive_keys_bn(struct ssh *ssh, u_char *hash, u_int hashlen,
    const BIGNUM *secret)
{
	struct sshbuf *shared_secret;
	int r;

	if ((shared_secret = sshbuf_new()) == NULL)
		return SSH_ERR_ALLOC_FAIL;
	if ((r = sshbuf_put_bignum2(shared_secret, secret)) == 0)
		r = kex_derive_keys(ssh, hash, hashlen, shared_secret);
	sshbuf_free(shared_secret);
	return r;
}
