register_address(struct x86_emulate_ctxt *ctxt, unsigned long reg)
{
	return address_mask(ctxt, reg);
}
