static inline void __vmx_flush_tlb(struct kvm_vcpu *vcpu, int vpid,
				bool invalidate_gpa)
{
	if (enable_ept && (invalidate_gpa || !enable_vpid)) {
		if (!VALID_PAGE(vcpu->arch.mmu.root_hpa))
			return;
		ept_sync_context(construct_eptp(vcpu, vcpu->arch.mmu.root_hpa));
	} else {
		vpid_sync_context(vpid);
	}
}
