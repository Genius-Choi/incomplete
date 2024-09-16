static ulong *reg_write(struct x86_emulate_ctxt *ctxt, unsigned nr)
{
	ctxt->regs_valid |= 1 << nr;
	ctxt->regs_dirty |= 1 << nr;
	return &ctxt->_regs[nr];
}
