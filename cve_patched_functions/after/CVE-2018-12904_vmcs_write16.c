static __always_inline void vmcs_write16(unsigned long field, u16 value)
{
	vmcs_check16(field);
	if (static_branch_unlikely(&enable_evmcs))
		return evmcs_write16(field, value);

	__vmcs_writel(field, value);
}
