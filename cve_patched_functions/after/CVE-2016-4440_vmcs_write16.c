static __always_inline void vmcs_write16(unsigned long field, u16 value)
{
	vmcs_check16(field);
	__vmcs_writel(field, value);
}
