register_address_increment(struct x86_emulate_ctxt *ctxt, int reg, int inc)
{
	ulong *preg = reg_rmw(ctxt, reg);

	assign_register(preg, *preg + inc, ctxt->ad_bytes);
}
