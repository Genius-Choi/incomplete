int kvm_arch_hardware_enable(void *garbage)
{
	struct kvm *kvm;
	struct kvm_vcpu *vcpu;
	int i;

	kvm_shared_msr_cpu_online();
	list_for_each_entry(kvm, &vm_list, vm_list)
		kvm_for_each_vcpu(i, vcpu, kvm)
			if (vcpu->cpu == smp_processor_id())
				kvm_make_request(KVM_REQ_CLOCK_UPDATE, vcpu);
	return kvm_x86_ops->hardware_enable(garbage);
}
