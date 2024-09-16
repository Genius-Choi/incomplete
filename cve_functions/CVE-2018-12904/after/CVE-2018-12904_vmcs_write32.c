static __always_inline void vmcs_write32(unsigned long field, u32 value)
{
	vmcs_check32(field);
	if (static_branch_unlikely(&enable_evmcs))
		return evmcs_write32(field, value);

	__vmcs_writel(field, value);
}
