void camellia_decrypt_cbc_2way(void *ctx, u128 *dst, const u128 *src)
{
	u128 iv = *src;

	camellia_dec_blk_2way(ctx, (u8 *)dst, (u8 *)src);

	u128_xor(&dst[1], &dst[1], &iv);
}
