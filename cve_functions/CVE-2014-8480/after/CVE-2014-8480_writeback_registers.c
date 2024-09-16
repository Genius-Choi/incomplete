static void writeback_registers(struct x86_emulate_ctxt *ctxt)
{
	unsigned reg;

	for_each_set_bit(reg, (ulong *)&ctxt->regs_dirty, 16)
		ctxt->ops->write_gpr(ctxt, reg, ctxt->_regs[reg]);
}
