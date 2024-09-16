static void unaccount_shadowed(struct kvm *kvm, gfn_t gfn)
{
	struct kvm_memory_slot *slot;
	struct kvm_lpage_info *linfo;
	int i;

	slot = gfn_to_memslot(kvm, gfn);
	for (i = PT_DIRECTORY_LEVEL;
	     i < PT_PAGE_TABLE_LEVEL + KVM_NR_PAGE_SIZES; ++i) {
		linfo = lpage_info_slot(gfn, slot, i);
		linfo->write_count -= 1;
		WARN_ON(linfo->write_count < 0);
	}
	kvm->arch.indirect_shadow_pages--;
}
