static int emulator_cmpxchg_emulated(unsigned long addr,
				     const void *old,
				     const void *new,
				     unsigned int bytes,
				     struct x86_exception *exception,
				     struct kvm_vcpu *vcpu)
{
	gpa_t gpa;
	struct page *page;
	char *kaddr;
	bool exchanged;

	/* guests cmpxchg8b have to be emulated atomically */
	if (bytes > 8 || (bytes & (bytes - 1)))
		goto emul_write;

	gpa = kvm_mmu_gva_to_gpa_write(vcpu, addr, NULL);

	if (gpa == UNMAPPED_GVA ||
	    (gpa & PAGE_MASK) == APIC_DEFAULT_PHYS_BASE)
		goto emul_write;

	if (((gpa + bytes - 1) & PAGE_MASK) != (gpa & PAGE_MASK))
		goto emul_write;

	page = gfn_to_page(vcpu->kvm, gpa >> PAGE_SHIFT);
	if (is_error_page(page)) {
		kvm_release_page_clean(page);
		goto emul_write;
	}

	kaddr = kmap_atomic(page, KM_USER0);
	kaddr += offset_in_page(gpa);
	switch (bytes) {
	case 1:
		exchanged = CMPXCHG_TYPE(u8, kaddr, old, new);
		break;
	case 2:
		exchanged = CMPXCHG_TYPE(u16, kaddr, old, new);
		break;
	case 4:
		exchanged = CMPXCHG_TYPE(u32, kaddr, old, new);
		break;
	case 8:
		exchanged = CMPXCHG64(kaddr, old, new);
		break;
	default:
		BUG();
	}
	kunmap_atomic(kaddr, KM_USER0);
	kvm_release_page_dirty(page);

	if (!exchanged)
		return X86EMUL_CMPXCHG_FAILED;

	kvm_mmu_pte_write(vcpu, gpa, new, bytes, 1);

	return X86EMUL_CONTINUE;

emul_write:
	printk_once(KERN_WARNING "kvm: emulating exchange as write\n");

	return emulator_write_emulated(addr, new, bytes, exception, vcpu);
}
