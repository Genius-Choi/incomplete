static int md5_sparc64_init(struct shash_desc *desc)
{
	struct md5_state *mctx = shash_desc_ctx(desc);

	mctx->hash[0] = cpu_to_le32(0x67452301);
	mctx->hash[1] = cpu_to_le32(0xefcdab89);
	mctx->hash[2] = cpu_to_le32(0x98badcfe);
	mctx->hash[3] = cpu_to_le32(0x10325476);
	mctx->byte_count = 0;

	return 0;
}
