int kvm_unmap_hva_range(struct kvm *kvm, unsigned long start, unsigned long end)
{
	return kvm_handle_hva_range(kvm, start, end, 0, kvm_unmap_rmapp);
}
