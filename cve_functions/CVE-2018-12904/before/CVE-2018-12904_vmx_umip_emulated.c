static bool vmx_umip_emulated(void)
{
	return vmcs_config.cpu_based_2nd_exec_ctrl &
		SECONDARY_EXEC_DESC;
}
