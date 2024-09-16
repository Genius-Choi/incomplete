static __always_inline u16 vmcs_read16(unsigned long field)
{
	vmcs_check16(field);
	if (static_branch_unlikely(&enable_evmcs))
		return evmcs_read16(field);
	return __vmcs_readl(field);
}
