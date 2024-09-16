static int handle_cpuid(struct kvm_vcpu *vcpu)
{
	return kvm_emulate_cpuid(vcpu);
}
