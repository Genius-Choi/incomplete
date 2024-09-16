static int set_spte(struct kvm_vcpu *vcpu, u64 *sptep,
		    unsigned pte_access, int level,
		    gfn_t gfn, pfn_t pfn, bool speculative,
		    bool can_unsync, bool host_writable)
{
	u64 spte;
	int ret = 0;

	if (set_mmio_spte(vcpu->kvm, sptep, gfn, pfn, pte_access))
		return 0;

	spte = PT_PRESENT_MASK;
	if (!speculative)
		spte |= shadow_accessed_mask;

	if (pte_access & ACC_EXEC_MASK)
		spte |= shadow_x_mask;
	else
		spte |= shadow_nx_mask;

	if (pte_access & ACC_USER_MASK)
		spte |= shadow_user_mask;

	if (level > PT_PAGE_TABLE_LEVEL)
		spte |= PT_PAGE_SIZE_MASK;
	if (tdp_enabled)
		spte |= kvm_x86_ops->get_mt_mask(vcpu, gfn,
			kvm_is_mmio_pfn(pfn));

	if (host_writable)
		spte |= SPTE_HOST_WRITEABLE;
	else
		pte_access &= ~ACC_WRITE_MASK;

	spte |= (u64)pfn << PAGE_SHIFT;

	if (pte_access & ACC_WRITE_MASK) {

		/*
		 * Other vcpu creates new sp in the window between
		 * mapping_level() and acquiring mmu-lock. We can
		 * allow guest to retry the access, the mapping can
		 * be fixed if guest refault.
		 */
		if (level > PT_PAGE_TABLE_LEVEL &&
		    has_wrprotected_page(vcpu->kvm, gfn, level))
			goto done;

		spte |= PT_WRITABLE_MASK | SPTE_MMU_WRITEABLE;

		/*
		 * Optimization: for pte sync, if spte was writable the hash
		 * lookup is unnecessary (and expensive). Write protection
		 * is responsibility of mmu_get_page / kvm_sync_page.
		 * Same reasoning can be applied to dirty page accounting.
		 */
		if (!can_unsync && is_writable_pte(*sptep))
			goto set_pte;

		if (mmu_need_write_protect(vcpu, gfn, can_unsync)) {
			pgprintk("%s: found shadow page for %llx, marking ro\n",
				 __func__, gfn);
			ret = 1;
			pte_access &= ~ACC_WRITE_MASK;
			spte &= ~(PT_WRITABLE_MASK | SPTE_MMU_WRITEABLE);
		}
	}

	if (pte_access & ACC_WRITE_MASK)
		mark_page_dirty(vcpu->kvm, gfn);

set_pte:
	if (mmu_spte_update(sptep, spte))
		kvm_flush_remote_tlbs(vcpu->kvm);
done:
	return ret;
}
