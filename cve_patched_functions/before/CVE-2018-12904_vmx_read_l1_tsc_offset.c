static u64 vmx_read_l1_tsc_offset(struct kvm_vcpu *vcpu)
{
	struct vmcs12 *vmcs12 = get_vmcs12(vcpu);

	if (is_guest_mode(vcpu) &&
	    (vmcs12->cpu_based_vm_exec_control & CPU_BASED_USE_TSC_OFFSETING))
		return vcpu->arch.tsc_offset - vmcs12->tsc_offset;

	return vcpu->arch.tsc_offset;
}
