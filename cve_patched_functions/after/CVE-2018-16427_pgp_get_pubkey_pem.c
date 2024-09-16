pgp_get_pubkey_pem(sc_card_t *card, unsigned int tag, u8 *buf, size_t buf_len)
{
	struct pgp_priv_data *priv = DRVDATA(card);
	pgp_blob_t	*blob, *mod_blob, *exp_blob;
	sc_pkcs15_pubkey_t pubkey;
	u8		*data;
	size_t		len;
	int		r;

	sc_log(card->ctx, "called, tag=%04x\n", tag);

	if ((r = pgp_get_blob(card, priv->mf, tag & 0xFFFE, &blob)) < 0
		|| (r = pgp_get_blob(card, blob, 0x7F49, &blob)) < 0
		|| (r = pgp_get_blob(card, blob, 0x0081, &mod_blob)) < 0
		|| (r = pgp_get_blob(card, blob, 0x0082, &exp_blob)) < 0
		|| (r = pgp_read_blob(card, mod_blob)) < 0
		|| (r = pgp_read_blob(card, exp_blob)) < 0)
		LOG_TEST_RET(card->ctx, r, "error getting elements");

	memset(&pubkey, 0, sizeof(pubkey));
	pubkey.algorithm = SC_ALGORITHM_RSA;
	pubkey.u.rsa.modulus.data  = mod_blob->data;
	pubkey.u.rsa.modulus.len   = mod_blob->len;
	pubkey.u.rsa.exponent.data = exp_blob->data;
	pubkey.u.rsa.exponent.len  = exp_blob->len;

	r = sc_pkcs15_encode_pubkey(card->ctx, &pubkey, &data, &len);
	LOG_TEST_RET(card->ctx, r, "public key encoding failed");

	if (len > buf_len)
		len = buf_len;
	memcpy(buf, data, len);
	free(data);

	LOG_FUNC_RETURN(card->ctx, (int)len);
}
