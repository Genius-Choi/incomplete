static inline unsigned nested_cpu_vmx_misc_cr3_count(struct kvm_vcpu *vcpu)
{
	return vmx_misc_cr3_count(to_vmx(vcpu)->nested.msrs.misc_low);
}
