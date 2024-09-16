static int calc_hash(struct crypto_shash *tfm, u8 *digest,
		     const u8 *buf, unsigned int buflen)
{
	SHASH_DESC_ON_STACK(desc, tfm);
	int err;

	desc->tfm = tfm;
	desc->flags = 0;

	err = crypto_shash_digest(desc, buf, buflen, digest);
	shash_desc_zero(desc);
	return err;
}
