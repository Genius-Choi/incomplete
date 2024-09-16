static void vmx_flush_tlb(struct kvm_vcpu *vcpu, bool invalidate_gpa)
{
	__vmx_flush_tlb(vcpu, to_vmx(vcpu)->vpid, invalidate_gpa);
}
