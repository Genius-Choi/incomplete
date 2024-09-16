register_address_increment(struct x86_emulate_ctxt *ctxt, unsigned long *reg, int inc)
{
	ulong mask;

	if (ctxt->ad_bytes == sizeof(unsigned long))
		mask = ~0UL;
	else
		mask = ad_mask(ctxt);
	masked_increment(reg, mask, inc);
}
