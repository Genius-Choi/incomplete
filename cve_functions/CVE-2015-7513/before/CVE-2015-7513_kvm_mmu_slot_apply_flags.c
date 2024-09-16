static void kvm_mmu_slot_apply_flags(struct kvm *kvm,
				     struct kvm_memory_slot *new)
{
	/* Still write protect RO slot */
	if (new->flags & KVM_MEM_READONLY) {
		kvm_mmu_slot_remove_write_access(kvm, new);
		return;
	}

	/*
	 * Call kvm_x86_ops dirty logging hooks when they are valid.
	 *
	 * kvm_x86_ops->slot_disable_log_dirty is called when:
	 *
	 *  - KVM_MR_CREATE with dirty logging is disabled
	 *  - KVM_MR_FLAGS_ONLY with dirty logging is disabled in new flag
	 *
	 * The reason is, in case of PML, we need to set D-bit for any slots
	 * with dirty logging disabled in order to eliminate unnecessary GPA
	 * logging in PML buffer (and potential PML buffer full VMEXT). This
	 * guarantees leaving PML enabled during guest's lifetime won't have
	 * any additonal overhead from PML when guest is running with dirty
	 * logging disabled for memory slots.
	 *
	 * kvm_x86_ops->slot_enable_log_dirty is called when switching new slot
	 * to dirty logging mode.
	 *
	 * If kvm_x86_ops dirty logging hooks are invalid, use write protect.
	 *
	 * In case of write protect:
	 *
	 * Write protect all pages for dirty logging.
	 *
	 * All the sptes including the large sptes which point to this
	 * slot are set to readonly. We can not create any new large
	 * spte on this slot until the end of the logging.
	 *
	 * See the comments in fast_page_fault().
	 */
	if (new->flags & KVM_MEM_LOG_DIRTY_PAGES) {
		if (kvm_x86_ops->slot_enable_log_dirty)
			kvm_x86_ops->slot_enable_log_dirty(kvm, new);
		else
			kvm_mmu_slot_remove_write_access(kvm, new);
	} else {
		if (kvm_x86_ops->slot_disable_log_dirty)
			kvm_x86_ops->slot_disable_log_dirty(kvm, new);
	}
}
