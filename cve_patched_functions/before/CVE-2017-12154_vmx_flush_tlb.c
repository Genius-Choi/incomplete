static void vmx_flush_tlb(struct kvm_vcpu *vcpu)
{
	__vmx_flush_tlb(vcpu, to_vmx(vcpu)->vpid);
}
