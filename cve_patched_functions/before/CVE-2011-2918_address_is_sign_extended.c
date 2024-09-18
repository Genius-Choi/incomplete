static int address_is_sign_extended(__u64 a)
{
	__u64 b;
#if (NEFF == 32)
	b = (__u64)(__s64)(__s32)(a & 0xffffffffUL);
	return (b == a) ? 1 : 0;
#else
#error "Sign extend check only works for NEFF==32"
#endif
}
