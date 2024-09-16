static inline bool nested_cpu_has_nmi_exiting(struct vmcs12 *vmcs12)
{
	return vmcs12->pin_based_vm_exec_control & PIN_BASED_NMI_EXITING;
}
