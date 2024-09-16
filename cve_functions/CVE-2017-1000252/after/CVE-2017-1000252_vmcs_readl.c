static __always_inline unsigned long vmcs_readl(unsigned long field)
{
	vmcs_checkl(field);
	return __vmcs_readl(field);
}
