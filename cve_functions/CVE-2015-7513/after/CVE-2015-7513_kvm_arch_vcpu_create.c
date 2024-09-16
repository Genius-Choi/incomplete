struct kvm_vcpu *kvm_arch_vcpu_create(struct kvm *kvm,
						unsigned int id)
{
	struct kvm_vcpu *vcpu;

	if (check_tsc_unstable() && atomic_read(&kvm->online_vcpus) != 0)
		printk_once(KERN_WARNING
		"kvm: SMP vm created on host with unstable TSC; "
		"guest TSC will not be reliable\n");

	vcpu = kvm_x86_ops->vcpu_create(kvm, id);

	return vcpu;
}
