int  __attribute__((weak)) kvm_arch_update_irqfd_routing(
				struct kvm *kvm, unsigned int host_irq,
				uint32_t guest_irq, bool set)
{
	return 0;
}
