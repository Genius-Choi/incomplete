static __always_inline unsigned long vmcs_readl(unsigned long field)
{
	vmcs_checkl(field);
	if (static_branch_unlikely(&enable_evmcs))
		return evmcs_read64(field);
	return __vmcs_readl(field);
}
