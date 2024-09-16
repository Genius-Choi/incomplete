static __always_inline void vmcs_write64(unsigned long field, u64 value)
{
	vmcs_check64(field);
	__vmcs_writel(field, value);
#ifndef CONFIG_X86_64
	asm volatile ("");
	__vmcs_writel(field+1, value >> 32);
#endif
}
