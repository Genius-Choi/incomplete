static __always_inline void vmcs_writel(unsigned long field, unsigned long value)
{
	vmcs_checkl(field);
	if (static_branch_unlikely(&enable_evmcs))
		return evmcs_write64(field, value);

	__vmcs_writel(field, value);
}
