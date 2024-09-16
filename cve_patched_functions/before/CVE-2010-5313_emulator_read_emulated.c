static int emulator_read_emulated(unsigned long addr,
				  void *val,
				  unsigned int bytes,
				  struct x86_exception *exception,
				  struct kvm_vcpu *vcpu)
{
	gpa_t                 gpa;

	if (vcpu->mmio_read_completed) {
		memcpy(val, vcpu->mmio_data, bytes);
		trace_kvm_mmio(KVM_TRACE_MMIO_READ, bytes,
			       vcpu->mmio_phys_addr, *(u64 *)val);
		vcpu->mmio_read_completed = 0;
		return X86EMUL_CONTINUE;
	}

	gpa = kvm_mmu_gva_to_gpa_read(vcpu, addr, exception);

	if (gpa == UNMAPPED_GVA)
		return X86EMUL_PROPAGATE_FAULT;

	/* For APIC access vmexit */
	if ((gpa & PAGE_MASK) == APIC_DEFAULT_PHYS_BASE)
		goto mmio;

	if (kvm_read_guest_virt(addr, val, bytes, vcpu, exception)
	    == X86EMUL_CONTINUE)
		return X86EMUL_CONTINUE;

mmio:
	/*
	 * Is this MMIO handled locally?
	 */
	if (!vcpu_mmio_read(vcpu, gpa, bytes, val)) {
		trace_kvm_mmio(KVM_TRACE_MMIO_READ, bytes, gpa, *(u64 *)val);
		return X86EMUL_CONTINUE;
	}

	trace_kvm_mmio(KVM_TRACE_MMIO_READ_UNSATISFIED, bytes, gpa, 0);

	vcpu->mmio_needed = 1;
	vcpu->run->exit_reason = KVM_EXIT_MMIO;
	vcpu->run->mmio.phys_addr = vcpu->mmio_phys_addr = gpa;
	vcpu->run->mmio.len = vcpu->mmio_size = bytes;
	vcpu->run->mmio.is_write = vcpu->mmio_is_write = 0;

	return X86EMUL_IO_NEEDED;
}
