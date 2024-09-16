static int emulator_write_emulated_onepage(unsigned long addr,
					   const void *val,
					   unsigned int bytes,
					   struct x86_exception *exception,
					   struct kvm_vcpu *vcpu)
{
	gpa_t                 gpa;

	gpa = kvm_mmu_gva_to_gpa_write(vcpu, addr, exception);

	if (gpa == UNMAPPED_GVA)
		return X86EMUL_PROPAGATE_FAULT;

	/* For APIC access vmexit */
	if ((gpa & PAGE_MASK) == APIC_DEFAULT_PHYS_BASE)
		goto mmio;

	if (emulator_write_phys(vcpu, gpa, val, bytes))
		return X86EMUL_CONTINUE;

mmio:
	trace_kvm_mmio(KVM_TRACE_MMIO_WRITE, bytes, gpa, *(u64 *)val);
	/*
	 * Is this MMIO handled locally?
	 */
	if (!vcpu_mmio_write(vcpu, gpa, bytes, val))
		return X86EMUL_CONTINUE;

	vcpu->mmio_needed = 1;
	vcpu->run->exit_reason = KVM_EXIT_MMIO;
	vcpu->run->mmio.phys_addr = vcpu->mmio_phys_addr = gpa;
	vcpu->run->mmio.len = vcpu->mmio_size = bytes;
	vcpu->run->mmio.is_write = vcpu->mmio_is_write = 1;
	memcpy(vcpu->run->mmio.data, val, bytes);

	return X86EMUL_CONTINUE;
}
