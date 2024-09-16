void kvm_arch_vcpu_put(struct kvm_vcpu *vcpu)
{
	kvm_arm_set_running_vcpu(NULL);
}
