static void kvm_arm_set_running_vcpu(struct kvm_vcpu *vcpu)
{
	BUG_ON(preemptible());
	__get_cpu_var(kvm_arm_running_vcpu) = vcpu;
}
