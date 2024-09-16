static ulong reg_read(struct x86_emulate_ctxt *ctxt, unsigned nr)
{
	if (!(ctxt->regs_valid & (1 << nr))) {
		ctxt->regs_valid |= 1 << nr;
		ctxt->_regs[nr] = ctxt->ops->read_gpr(ctxt, nr);
	}
	return ctxt->_regs[nr];
}
