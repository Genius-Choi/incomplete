int kvm_set_cr4(struct kvm_vcpu *vcpu, unsigned long cr4)
{
	unsigned long old_cr4 = kvm_read_cr4(vcpu);
	unsigned long pdptr_bits = X86_CR4_PGE | X86_CR4_PSE | X86_CR4_PAE;

	if (cr4 & CR4_RESERVED_BITS)
		return 1;

	if (!guest_cpuid_has_xsave(vcpu) && (cr4 & X86_CR4_OSXSAVE))
		return 1;

	if (is_long_mode(vcpu)) {
		if (!(cr4 & X86_CR4_PAE))
			return 1;
	} else if (is_paging(vcpu) && (cr4 & X86_CR4_PAE)
		   && ((cr4 ^ old_cr4) & pdptr_bits)
		   && !load_pdptrs(vcpu, vcpu->arch.walk_mmu, vcpu->arch.cr3))
		return 1;

	if (cr4 & X86_CR4_VMXE)
		return 1;

	kvm_x86_ops->set_cr4(vcpu, cr4);

	if ((cr4 ^ old_cr4) & pdptr_bits)
		kvm_mmu_reset_context(vcpu);

	if ((cr4 ^ old_cr4) & X86_CR4_OSXSAVE)
		update_cpuid(vcpu);

	return 0;
}
