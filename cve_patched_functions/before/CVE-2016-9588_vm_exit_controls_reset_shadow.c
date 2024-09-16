static inline void vm_exit_controls_reset_shadow(struct vcpu_vmx *vmx)
{
	vmx->vm_exit_controls_shadow = vmcs_read32(VM_EXIT_CONTROLS);
}
