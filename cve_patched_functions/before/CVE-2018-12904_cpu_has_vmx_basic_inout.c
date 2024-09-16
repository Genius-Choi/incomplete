static inline bool cpu_has_vmx_basic_inout(void)
{
	return	(((u64)vmcs_config.basic_cap << 32) & VMX_BASIC_INOUT);
}
