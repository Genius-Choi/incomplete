static inline bool cpu_has_vmx_preemption_timer(void)
{
	return vmcs_config.pin_based_exec_ctrl &
		PIN_BASED_VMX_PREEMPTION_TIMER;
}
