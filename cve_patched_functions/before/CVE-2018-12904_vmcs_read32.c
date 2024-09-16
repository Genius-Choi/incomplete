static __always_inline u32 vmcs_read32(unsigned long field)
{
	vmcs_check32(field);
	if (static_branch_unlikely(&enable_evmcs))
		return evmcs_read32(field);
	return __vmcs_readl(field);
}
