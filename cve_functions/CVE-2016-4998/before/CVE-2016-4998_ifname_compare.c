static unsigned long ifname_compare(const char *_a, const char *_b, const char *_mask)
{
#ifdef CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	unsigned long ret = ifname_compare_aligned(_a, _b, _mask);
#else
	unsigned long ret = 0;
	const u16 *a = (const u16 *)_a;
	const u16 *b = (const u16 *)_b;
	const u16 *mask = (const u16 *)_mask;
	int i;

	for (i = 0; i < IFNAMSIZ/sizeof(u16); i++)
		ret |= (a[i] ^ b[i]) & mask[i];
#endif
	return ret;
}
