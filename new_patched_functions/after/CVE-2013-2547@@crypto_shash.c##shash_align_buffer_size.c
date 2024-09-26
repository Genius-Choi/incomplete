static inline unsigned int shash_align_buffer_size(unsigned len,
						   unsigned long mask)
{
	return len + (mask & ~(__alignof__(u8 __attribute__ ((aligned))) - 1));
}
