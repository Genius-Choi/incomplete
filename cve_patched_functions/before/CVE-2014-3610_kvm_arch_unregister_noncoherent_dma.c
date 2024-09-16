void kvm_arch_unregister_noncoherent_dma(struct kvm *kvm)
{
	atomic_dec(&kvm->arch.noncoherent_dma_count);
}
