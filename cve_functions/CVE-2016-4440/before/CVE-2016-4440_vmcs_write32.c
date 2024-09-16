static __always_inline void vmcs_write32(unsigned long field, u32 value)
{
	vmcs_check32(field);
	__vmcs_writel(field, value);
}
