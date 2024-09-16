static void irqfd_update(struct kvm *kvm, struct kvm_kernel_irqfd *irqfd)
{
	struct kvm_kernel_irq_routing_entry *e;
	struct kvm_kernel_irq_routing_entry entries[KVM_NR_IRQCHIPS];
	int n_entries;

	n_entries = kvm_irq_map_gsi(kvm, entries, irqfd->gsi);

	write_seqcount_begin(&irqfd->irq_entry_sc);

	e = entries;
	if (n_entries == 1)
		irqfd->irq_entry = *e;
	else
		irqfd->irq_entry.type = 0;

	write_seqcount_end(&irqfd->irq_entry_sc);
}
