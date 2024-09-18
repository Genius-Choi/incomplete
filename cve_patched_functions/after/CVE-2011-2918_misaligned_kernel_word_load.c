static void misaligned_kernel_word_load(__u64 address, int do_sign_extend, __u64 *result)
{
	unsigned short x;
	unsigned char *p, *q;
	p = (unsigned char *) (int) address;
	q = (unsigned char *) &x;
	q[0] = p[0];
	q[1] = p[1];

	if (do_sign_extend) {
		*result = (__u64)(__s64) *(short *) &x;
	} else {
		*result = (__u64) x;
	}
}
