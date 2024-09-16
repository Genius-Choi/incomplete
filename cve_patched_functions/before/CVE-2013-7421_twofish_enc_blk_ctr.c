void twofish_enc_blk_ctr(void *ctx, u128 *dst, const u128 *src, le128 *iv)
{
	be128 ctrblk;

	if (dst != src)
		*dst = *src;

	le128_to_be128(&ctrblk, iv);
	le128_inc(iv);

	twofish_enc_blk(ctx, (u8 *)&ctrblk, (u8 *)&ctrblk);
	u128_xor(dst, dst, (u128 *)&ctrblk);
}
