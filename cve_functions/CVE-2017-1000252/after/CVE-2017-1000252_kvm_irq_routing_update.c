void kvm_irq_routing_update(struct kvm *kvm)
{
	struct kvm_kernel_irqfd *irqfd;

	spin_lock_irq(&kvm->irqfds.lock);

	list_for_each_entry(irqfd, &kvm->irqfds.items, list) {
		irqfd_update(kvm, irqfd);

#ifdef CONFIG_HAVE_KVM_IRQ_BYPASS
		if (irqfd->producer) {
			int ret = kvm_arch_update_irqfd_routing(
					irqfd->kvm, irqfd->producer->irq,
					irqfd->gsi, 1);
			WARN_ON(ret);
		}
#endif
	}

	spin_unlock_irq(&kvm->irqfds.lock);
}
