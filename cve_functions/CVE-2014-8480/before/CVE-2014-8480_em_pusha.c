static int em_pusha(struct x86_emulate_ctxt *ctxt)
{
	unsigned long old_esp = reg_read(ctxt, VCPU_REGS_RSP);
	int rc = X86EMUL_CONTINUE;
	int reg = VCPU_REGS_RAX;

	while (reg <= VCPU_REGS_RDI) {
		(reg == VCPU_REGS_RSP) ?
		(ctxt->src.val = old_esp) : (ctxt->src.val = reg_read(ctxt, reg));

		rc = em_push(ctxt);
		if (rc != X86EMUL_CONTINUE)
			return rc;

		++reg;
	}

	return rc;
}
