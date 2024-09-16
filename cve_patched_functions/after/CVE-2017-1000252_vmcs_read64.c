static __always_inline u64 vmcs_read64(unsigned long field)
{
	vmcs_check64(field);
#ifdef CONFIG_X86_64
	return __vmcs_readl(field);
#else
	return __vmcs_readl(field) | ((u64)__vmcs_readl(field+1) << 32);
#endif
}
