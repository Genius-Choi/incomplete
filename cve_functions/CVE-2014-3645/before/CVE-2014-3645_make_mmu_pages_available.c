static void make_mmu_pages_available(struct kvm_vcpu *vcpu)
{
	LIST_HEAD(invalid_list);

	if (likely(kvm_mmu_available_pages(vcpu->kvm) >= KVM_MIN_FREE_MMU_PAGES))
		return;

	while (kvm_mmu_available_pages(vcpu->kvm) < KVM_REFILL_PAGES) {
		if (!prepare_zap_oldest_mmu_page(vcpu->kvm, &invalid_list))
			break;

		++vcpu->kvm->stat.mmu_recycled;
	}
	kvm_mmu_commit_zap_page(vcpu->kvm, &invalid_list);
}
