static int kvm_sync_page_transient(struct kvm_vcpu *vcpu,
				   struct kvm_mmu_page *sp)
{
	LIST_HEAD(invalid_list);
	int ret;

	ret = __kvm_sync_page(vcpu, sp, &invalid_list, false);
	if (ret)
		kvm_mmu_commit_zap_page(vcpu->kvm, &invalid_list);

	return ret;
}
