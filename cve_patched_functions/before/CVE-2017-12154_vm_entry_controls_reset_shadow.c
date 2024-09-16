static inline void vm_entry_controls_reset_shadow(struct vcpu_vmx *vmx)
{
	vmx->vm_entry_controls_shadow = vmcs_read32(VM_ENTRY_CONTROLS);
}
