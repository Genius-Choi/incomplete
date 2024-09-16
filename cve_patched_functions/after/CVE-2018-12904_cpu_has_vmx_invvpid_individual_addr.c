static inline bool cpu_has_vmx_invvpid_individual_addr(void)
{
	return vmx_capability.vpid & VMX_VPID_EXTENT_INDIVIDUAL_ADDR_BIT;
}
