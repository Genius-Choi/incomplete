static int em_cpuid(struct x86_emulate_ctxt *ctxt)
{
	u32 eax, ebx, ecx, edx;

	eax = reg_read(ctxt, VCPU_REGS_RAX);
	ecx = reg_read(ctxt, VCPU_REGS_RCX);
	ctxt->ops->get_cpuid(ctxt, &eax, &ebx, &ecx, &edx);
	*reg_write(ctxt, VCPU_REGS_RAX) = eax;
	*reg_write(ctxt, VCPU_REGS_RBX) = ebx;
	*reg_write(ctxt, VCPU_REGS_RCX) = ecx;
	*reg_write(ctxt, VCPU_REGS_RDX) = edx;
	return X86EMUL_CONTINUE;
}
