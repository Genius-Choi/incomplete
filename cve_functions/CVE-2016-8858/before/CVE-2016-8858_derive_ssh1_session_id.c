derive_ssh1_session_id(BIGNUM *host_modulus, BIGNUM *server_modulus,
    u_int8_t cookie[8], u_int8_t id[16])
{
	u_int8_t hbuf[2048], sbuf[2048], obuf[SSH_DIGEST_MAX_LENGTH];
	struct ssh_digest_ctx *hashctx = NULL;
	size_t hlen, slen;
	int r;

	hlen = BN_num_bytes(host_modulus);
	slen = BN_num_bytes(server_modulus);
	if (hlen < (512 / 8) || (u_int)hlen > sizeof(hbuf) ||
	    slen < (512 / 8) || (u_int)slen > sizeof(sbuf))
		return SSH_ERR_KEY_BITS_MISMATCH;
	if (BN_bn2bin(host_modulus, hbuf) <= 0 ||
	    BN_bn2bin(server_modulus, sbuf) <= 0) {
		r = SSH_ERR_LIBCRYPTO_ERROR;
		goto out;
	}
	if ((hashctx = ssh_digest_start(SSH_DIGEST_MD5)) == NULL) {
		r = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	if (ssh_digest_update(hashctx, hbuf, hlen) != 0 ||
	    ssh_digest_update(hashctx, sbuf, slen) != 0 ||
	    ssh_digest_update(hashctx, cookie, 8) != 0 ||
	    ssh_digest_final(hashctx, obuf, sizeof(obuf)) != 0) {
		r = SSH_ERR_LIBCRYPTO_ERROR;
		goto out;
	}
	memcpy(id, obuf, ssh_digest_bytes(SSH_DIGEST_MD5));
	r = 0;
 out:
	ssh_digest_free(hashctx);
	explicit_bzero(hbuf, sizeof(hbuf));
	explicit_bzero(sbuf, sizeof(sbuf));
	explicit_bzero(obuf, sizeof(obuf));
	return r;
}
