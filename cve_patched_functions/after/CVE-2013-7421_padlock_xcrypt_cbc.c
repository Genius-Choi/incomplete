static inline u8 *padlock_xcrypt_cbc(const u8 *input, u8 *output, void *key,
				     u8 *iv, void *control_word, u32 count)
{
	u32 initial = count & (cbc_fetch_blocks - 1);

	if (count < cbc_fetch_blocks)
		return cbc_crypt(input, output, key, iv, control_word, count);

	if (initial)
		asm volatile (".byte 0xf3,0x0f,0xa7,0xd0"	/* rep xcryptcbc */
			      : "+S" (input), "+D" (output), "+a" (iv)
			      : "d" (control_word), "b" (key), "c" (initial));

	asm volatile (".byte 0xf3,0x0f,0xa7,0xd0"	/* rep xcryptcbc */
		      : "+S" (input), "+D" (output), "+a" (iv)
		      : "d" (control_word), "b" (key), "c" (count-initial));
	return iv;
}
