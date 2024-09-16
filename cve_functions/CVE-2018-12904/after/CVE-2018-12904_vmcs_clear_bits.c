static __always_inline void vmcs_clear_bits(unsigned long field, u32 mask)
{
        BUILD_BUG_ON_MSG(__builtin_constant_p(field) && ((field) & 0x6000) == 0x2000,
			 "vmcs_clear_bits does not support 64-bit fields");
	if (static_branch_unlikely(&enable_evmcs))
		return evmcs_write32(field, evmcs_read32(field) & ~mask);

	__vmcs_writel(field, __vmcs_readl(field) & ~mask);
}
