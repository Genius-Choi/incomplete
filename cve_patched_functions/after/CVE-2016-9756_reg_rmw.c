static ulong *reg_rmw(struct x86_emulate_ctxt *ctxt, unsigned nr)
{
	reg_read(ctxt, nr);
	return reg_write(ctxt, nr);
}
