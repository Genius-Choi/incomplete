struct kvm_vcpu *kvm_arm_get_running_vcpu(void)
{
	BUG_ON(preemptible());
	return __get_cpu_var(kvm_arm_running_vcpu);
}
