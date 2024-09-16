static void vmx_cancel_hv_timer(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	vmx->hv_deadline_tsc = -1;
	vmcs_clear_bits(PIN_BASED_VM_EXEC_CONTROL,
			PIN_BASED_VMX_PREEMPTION_TIMER);
}
