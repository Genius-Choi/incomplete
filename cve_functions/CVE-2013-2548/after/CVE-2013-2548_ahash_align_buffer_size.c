static inline unsigned int ahash_align_buffer_size(unsigned len,
						   unsigned long mask)
{
	return len + (mask & ~(crypto_tfm_ctx_alignment() - 1));
}
