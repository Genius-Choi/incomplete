static __always_inline u16 vmcs_read16(unsigned long field)
{
	vmcs_check16(field);
	return __vmcs_readl(field);
}
