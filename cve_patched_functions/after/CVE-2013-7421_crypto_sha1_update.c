int crypto_sha1_update(struct shash_desc *desc, const u8 *data,
			unsigned int len)
{
	struct sha1_state *sctx = shash_desc_ctx(desc);
	unsigned int partial, done;
	const u8 *src;

	partial = sctx->count % SHA1_BLOCK_SIZE;
	sctx->count += len;
	done = 0;
	src = data;

	if ((partial + len) >= SHA1_BLOCK_SIZE) {
		u32 temp[SHA_WORKSPACE_WORDS];

		if (partial) {
			done = -partial;
			memcpy(sctx->buffer + partial, data,
			       done + SHA1_BLOCK_SIZE);
			src = sctx->buffer;
		}

		do {
			sha_transform(sctx->state, src, temp);
			done += SHA1_BLOCK_SIZE;
			src = data + done;
		} while (done + SHA1_BLOCK_SIZE <= len);

		memzero_explicit(temp, sizeof(temp));
		partial = 0;
	}
	memcpy(sctx->buffer + partial, src, len - done);

	return 0;
}
